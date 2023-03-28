#ifndef _BRKS_BUS_USERM_HANDLER_H_
#define _BRKS_BUS_USERM_HANDLER_H_

#include "iEventHandler.h"
#include "events_def.h"
#include "thread_pool/thread_mutex.h"

#include <map>

class UserEventHandler : public iEventHandler
{
public:
	UserEventHandler();
	virtual ~UserEventHandler();
	virtual iEvent* handler(const iEvent* ev);

private:
	MobileCodeRspEv* handle_mobile_code_req(MobileCodeReqEv *ev);
	i32 code_gen();

	std::string mobile_;
	std::map<std::string, i32 > m2c_;
	thread_mutex_t pm_;
};

#endif
