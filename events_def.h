#ifndef __BRKS_COMMON_EVENTS_DEF_H__
#define __BRKS_COMMON_EVENTS_DEF_H__

#include "ievent.h"
#include "bike.pb.h"
#include <string>

class MobileCodeReqEv : public iEvent
{
public:
	MobileCodeReqEv(const std::string& mobile) : iEvent(EEVENTID_GET_MOBLIE_CODE_REQ, iEvent::generateSegNo())
	{
		msg_.set_mobile(mobile);
	};

	const std::string& get_mobile() const { return msg_.mobile(); };
	virtual i32 ByteSize() { return msg_.ByteSize(); };
	virtual bool SerializeToArray(char* buf, int len) { return msg_.SerializeToArray(buf, len); };
	virtual std::ostream& dump(std::ostream& out) const;

private:
	tutorial::mobile_request msg_;
};

class MobileCodeRspEv :public iEvent
{
public:
	MobileCodeRspEv(i32 code, i32 icode) : iEvent(EEVENTID_GET_MOBLIE_CODE_RSP, iEvent::generateSegNo())
	{
		msg_.set_code(code);
		msg_.set_icode(icode);
		msg_.set_data(getReasonByErrorCode(code));
	};	

	const i32 get_code() const { return msg_.code(); };
	const i32 get_icode() const { return msg_.icode(); };
	const std::string& get_data() const { return msg_.data(); };

	virtual i32 ByteSize() { return msg_.ByteSize(); };
	virtual bool SerializeToArray(char* buf, int len) { return msg_.SerializeToArray(buf, len); };
	virtual std::ostream& dump(std::ostream& out) const;

private:
	tutorial::mobile_response msg_;
};

class ExitRspEv : public iEvent
{
public:
	ExitRspEv() : iEvent(EEVENTID_EXIT_RSP, iEvent::generateSegNo())
	{
	}

};

#endif
