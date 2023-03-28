#include "DispatchMsgService.h"
#include "NetworkInterface.h"
#include "eventtype.h"
#include "events_def.h"
#include <algorithm>

#include "bike.pb.h"

DispatchMsgService*  DispatchMsgService::DMS_ = nullptr;
std::queue<iEvent*> DispatchMsgService::response_events;
pthread_mutex_t DispatchMsgService::queue_mutex;

DispatchMsgService::DispatchMsgService()
{
	tp = nullptr;
}

DispatchMsgService::~DispatchMsgService()
{
}

BOOL DispatchMsgService::open()
{
	svr_exit_ = false;
	thread_mutex_create(&queue_mutex);

	tp = thread_pool_init();

	return tp ? TRUE : FALSE;
}

void DispatchMsgService::close()
{
	if (!svr_exit_) {
		thread_pool_destroy(tp);
		thread_mutex_destroy(&queue_mutex);
		tp = NULL;
		svr_exit_ = true;
	}
	subscribers_.clear();
}

void DispatchMsgService::subscribe(u32 eid, iEventHandler* handler)
{
	LOG_DEBUG("DispatchMsgService::subscribe eid: %u\n", eid);
	T_EventHandlersMap::iterator itor = subscribers_.find(eid);
	if (itor != subscribers_.end()) {
		T_EventHandlers::iterator eh_itor = std::find(itor->second.begin(), itor->second.end(), handler);
		if (eh_itor == itor->second.end()) {
			itor->second.push_back(handler);
		}
	}
	else {
		subscribers_[eid].push_back(handler);
	}
}

void DispatchMsgService::unsubscribe(u32 eid, iEventHandler* handler)
{
	T_EventHandlersMap::iterator itor = subscribers_.find(eid);
	if (itor != subscribers_.end()) {
		T_EventHandlers::iterator eh_itor = std::find(itor->second.begin(), itor->second.end(), handler);
		if (eh_itor != itor->second.end()) {
			itor->second.erase(eh_itor);
		}
	}
}

i32 DispatchMsgService::enqueue(iEvent* ev)
{
	if (NULL == ev) {
		return -1;
	}

	thread_task_t* task = thread_task_alloc(0);
	task->ctx = ev;
	task->handler = DispatchMsgService::svc;

	return (i32)thread_task_post(tp, task);
}

DispatchMsgService* DispatchMsgService::getInstance()
{
	if (DMS_ == nullptr) {
		DMS_ = new DispatchMsgService();
	}

	return DMS_;
}

void DispatchMsgService::svc(void* argv)
{
	DispatchMsgService* dms = DispatchMsgService::getInstance();
	iEvent* ev = (iEvent*)argv;
	
	if (!dms->svr_exit_) {
		LOG_DEBUG("DispatchMsgService::svc()...\n");
		iEvent* rsp = dms->process(ev);

		if (rsp) {
			rsp->dump(std::cout);
			rsp->set_args(ev->get_args());
		}
		else {
			//生成终止响应事件
			rsp = new ExitRspEv();
			rsp->set_args(ev->get_args());
		}

		thread_mutex_lock(&queue_mutex);
		response_events.push(rsp);
		thread_mutex_unlock(&queue_mutex);
	}
}

iEvent* DispatchMsgService::process(const iEvent* ev)
{
	LOG_DEBUG("DispatchMsgService::process() -ev: %p\n", ev);
	if (ev == nullptr) {
		return nullptr;
	}

	i32 eid = ev->get_eid();
	LOG_DEBUG("DispatchMsgService::process() -eid: %u\n", eid);

	if (eid == EEVENTID_UNKOWN) {
		LOG_WARN("DispatchMsgService : unknow  event_id: %d \n", eid);
		return nullptr;
	}

	iEvent* rsp = nullptr;

	T_EventHandlersMap::iterator itor = subscribers_.find(eid);
	if (itor != subscribers_.end()) {
		T_EventHandlers& eh = itor->second;
		for (T_EventHandlers::iterator eh_itor = eh.begin(); eh_itor != eh.end(); eh_itor++) {
			LOG_DEBUG("DispatchMsgService : get handler : %s\n", (*eh_itor)->get_name().c_str());
			rsp = (*eh_itor)->handler(ev);
		}
	}
	else {
		LOG_WARN("DispatchMsgService : no any event handler subscribed: %d \n", eid);
	}

	return rsp;
}

iEvent* DispatchMsgService::parseEvent(const char* message, u32 message_len, u16 eid)
{
	if (!message) {
		LOG_ERROR("DispatchMsgService::parseEvent - message is null. [eid:%d]\n", eid);
		return nullptr;
	}

	if (eid == EEVENTID_GET_MOBLIE_CODE_REQ) {
		tutorial::mobile_request mr;
		if (mr.ParseFromArray(message, message_len)) {
			MobileCodeReqEv* ev = new MobileCodeReqEv(mr.mobile());
			return ev;
		}
	}
	else if (eid == EEVENTID_LOGIN_REQ) {

	}

	return nullptr;
}

void DispatchMsgService::handleAllResponseEvent(NetworkInterface* interface)
{
	bool done = false;
	iEvent* ev = nullptr;

	while (!done) {
		thread_mutex_lock(&queue_mutex);

		if (response_events.empty()) done = true;
		else {
			ev = response_events.front();
			response_events.pop();
		}

		thread_mutex_unlock(&queue_mutex);

		if (!done) {
			if (ev->get_eid() == EEVENTID_GET_MOBLIE_CODE_RSP) {
				LOG_DEBUG("DispatchMsgService::handleAllResponseEvent - id: EEVENTID_GET_MOBLIE_CODE_RSP\n");
				MobileCodeRspEv* mcre = static_cast<MobileCodeRspEv*>(ev);
				ConnectSession* cs = (ConnectSession*)ev->get_args();
				cs->response = ev;

				cs->message_len = mcre->ByteSize();
				cs->write_buf = new char[cs->message_len + MESSAGE_HEADER_LEN];

				//组装头部
				memcpy(cs->write_buf, MESSAGE_HEADER_ID, strlen(MESSAGE_HEADER_ID));
				*(u16*)(cs->write_buf + 4) = EEVENTID_GET_MOBLIE_CODE_RSP;
				*(u32*)(cs->write_buf + 6) = cs->message_len;
				mcre->SerializeToArray(cs->write_buf + MESSAGE_HEADER_LEN, cs->message_len);

				interface->send_response_message(cs);
			}
			else if (ev->get_eid() == EEVENTID_EXIT_RSP) {
				ConnectSession* cs = (ConnectSession*)ev->get_args();
				delete ev;
				cs->response = nullptr;
				interface->send_response_message(cs);
			}
		}
	}
}