#include "events_def.h"
#include <iostream>
#include <sstream>

std::ostream& MobileCodeReqEv::dump(std::ostream& out) const
{
	out << "MobileCodeReq sn = " << get_sn() << ",";
	out << "mobile = " << msg_.mobile() << std::endl;
	out << std::endl;

	return out;
}

std::ostream& MobileCodeRspEv::dump(std::ostream& out) const
{
	out << "MobileCodeReq sn = " << get_sn() << std::endl;
	out << "code = " << get_code() << std::endl;
	out << "icode = " << get_icode() << std::endl;
	out << "data = " << get_data() << std::endl;
	out << std::endl;

	return out;
}