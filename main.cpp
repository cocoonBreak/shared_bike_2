#include <iostream>
#include <unistd.h>
#include "bike.pb.h"
#include "events_def.h"
#include "user_event_handler.h"
#include "DispatchMsgService.h"
#include "NetworkInterface.h"
#include "iniconfig.h"
#include "logger.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3) {
		printf("Please input shbk <config file path> <log file config>!\n");
		return -1;
	}

	if (!logger::get_instance().init(std::string(argv[2]))) {
		fprintf(stderr, "init log module failed.\n");
		return -2;
	}

	Iniconfig iniconf;
	if (!iniconf.loadfile(argv[1])) {
		LOG_ERROR("log %s failed.", argv[1]);
		return -3;
	}

	const st_env_config& st_conf = iniconf.getconfig();
	LOG_INFO("[datebase] ip: %s port: %d user: %s pwd: %s name: %s  [server] port:%d\n", st_conf.db_ip.c_str(), st_conf.db_port, \
		st_conf.db_user.c_str(), st_conf.db_pwd.c_str(), st_conf.db_name.c_str(), st_conf.svr_port);

	/*tutorial::mobile_request msg;
	msg.set_mobile("1234567");

	MobileCodeReqEv me("1234567");
	me.dump(cout);

	cout << msg.mobile() << endl;

	MobileCodeRspEv rsp(200, 8888);
	rsp.dump(cout);

	MobileCodeRspEv rsp2(ERRC_INVALID_DATA, 5555);
	rsp2.dump(cout);

	MobileCodeRspEv rsp3(ERRC_BIKE_IS_RUNNING, 1111);
	rsp3.dump(cout);

	UserEventHandler uehl;
	uehl.handler(&me);
	cout << endl;*/

	/*DispatchMsgService* pDS = DispatchMsgService::getInstance();
	pDS->open();
	MobileCodeReqEv* pMcre = new MobileCodeReqEv("13224322112");
	pDS->enqueue(pMcre);
	sleep(5);
	pDS->close();
	sleep(5);*/

	UserEventHandler uehl;

	DispatchMsgService* pDS = DispatchMsgService::getInstance();
	pDS->open();

	NetworkInterface NITF;
	NITF.start(8888);
	while (1) {
		NITF.network_event_dispatch();
		LOG_DEBUG("network_event_dispatch()...\n");
		sleep(1);
	}

	return 0;
}