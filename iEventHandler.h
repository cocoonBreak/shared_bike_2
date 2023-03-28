#ifndef _NS_IEVENT_HANDLER_H_
#define _NS_IEVENT_HANDLER_H_

#include "ievent.h"

class iEventHandler
{
public:
	iEventHandler(const char* name) :name_(name){};
	std::string get_name() { return name_; };
	virtual ~iEventHandler() {};
	virtual iEvent* handler(const iEvent* ev) { return NULL; };

private:
	std::string name_;
};

#endif
