#ifndef __DISPATCHMSGSERVICE_H__
#define __DISPATCHMSGSERVICE_H__

#include "ievent.h"
#include "iEventHandler.h"
#include "NetworkInterface.h"
#include "thread_pool/thread_pool.h"
#include <vector>
#include <map>
#include <queue>

class DispatchMsgService {
public:
	virtual ~DispatchMsgService();

	static DispatchMsgService* getInstance();

	virtual BOOL open();
	virtual void close();

	virtual void subscribe(u32 eid, iEventHandler* handler);
	virtual void unsubscribe(u32 eid, iEventHandler* handler);
	virtual i32 enqueue(iEvent* ev);

	static void svc(void* argv);
	virtual iEvent* process(const iEvent* ev);

	iEvent* parseEvent(const char* message, u32 message_len, u16 eid);

	void handleAllResponseEvent(NetworkInterface* interface);

protected:
	DispatchMsgService();

private:
	static DispatchMsgService* DMS_;
	thread_pool_t* tp;

	typedef std::vector<iEventHandler*> T_EventHandlers;
	typedef std::map<i32, T_EventHandlers> T_EventHandlersMap;
	T_EventHandlersMap subscribers_;

	static std::queue<iEvent*> response_events;
	static pthread_mutex_t queue_mutex;

	bool svr_exit_;
};

#endif
