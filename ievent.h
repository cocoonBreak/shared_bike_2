#ifndef _NS_EVENT_H_
#define _NS_EVENT_H_

#include "glo.def.h"
#include "eventtype.h"
#include <string>
#include <iostream>

class iEvent
{
public:
	iEvent(u32 eid, u32 sn);

	virtual ~iEvent();
	virtual i32 ByteSize() { return 0; };
	virtual bool SerializeToArray(char* buf, int len) { return true; };
	virtual std::ostream& dump(std::ostream& out) const { return out; };

	u32 generateSegNo();
	u32 get_eid() const { return eid_; };
	u32 get_sn() const { return sn_; };

	void set_eid(u32 eid) { eid_ = eid; };

	void set_args(void* args) { args_ = args; };
	void* get_args() { return args_; };

private:
	u32 eid_;
	u32 sn_;
	void* args_;
};

#endif