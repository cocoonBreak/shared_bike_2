#include "user_event_handler.h"
#include "DispatchMsgService.h"

UserEventHandler::UserEventHandler() : iEventHandler("UserEventHandler")
{
	//订阅事件
	DispatchMsgService::getInstance()->subscribe(EEVENTID_GET_MOBLIE_CODE_REQ, this);
	DispatchMsgService::getInstance()->subscribe(EEVENTID_LOGIN_REQ, this);
	thread_mutex_create(&pm_);
}

UserEventHandler::~UserEventHandler()
{
	//退订事件
	DispatchMsgService::getInstance()->unsubscribe(EEVENTID_GET_MOBLIE_CODE_REQ, this);
	DispatchMsgService::getInstance()->unsubscribe(EEVENTID_LOGIN_REQ, this);
	thread_mutex_destroy(&pm_);
}

iEvent* UserEventHandler::handler(const iEvent* ev)
{
	if (ev == NULL) {
		//LOG_ERROR("input ev is NULL.");
		printf("input ev is NULL.\n");
	}

	u32 eid = ev->get_eid();

	if(eid == EEVENTID_GET_MOBLIE_CODE_REQ)
	{
		return handle_mobile_code_req((MobileCodeReqEv*)ev);
	}
	else if (eid == EEVENTID_LOGIN_REQ)
	{
		//return handle_login_req((LoginEv*)ev);
	}
	
	return NULL;
}

MobileCodeRspEv* UserEventHandler::handle_mobile_code_req(MobileCodeReqEv* ev)
{
	std::string mobile_ = ev->get_mobile();
	//LOG_DEBUG("try to get mobile phone %s validate code.", mobile_.c_str());
	printf("try to get mobile phone %s validate code.\n", mobile_.c_str());

	i32 code = code_gen();
	thread_mutex_lock(&pm_);
	m2c_[mobile_] = code;
	thread_mutex_unlock(&pm_);
	printf("code = %d\n", code);
	
	return new MobileCodeRspEv(200, code);
}

i32 UserEventHandler::code_gen()
{
	i32 code = 0;
	srand((unsigned int)time(NULL));

	code = (unsigned int)(rand() % (999999 - 100000) + 100000);

	return code;
}