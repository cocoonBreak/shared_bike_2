#include "iniconfig.h"
#include <iniparser/iniparser.h>

Iniconfig::Iniconfig():_isloaded(false)
{
}

Iniconfig::~Iniconfig()
{
}

bool Iniconfig::loadfile(const std::string& path)
{
	dictionary *ini;
	
	if(!_isloaded){
		ini = iniparser_load(path.c_str());
		if(ini == NULL){
			fprintf(stderr, "cannot parse file: %s\n", path.c_str());
			return false;
		}

		_config.db_ip = iniparser_getstring(ini, "database:ip", "127.0.0.1");
		_config.db_port = iniparser_getint(ini, "database:port", 3306);
		_config.db_user = iniparser_getstring(ini, "database:user", "root");
		_config.db_pwd = iniparser_getstring(ini, "database:pwd", "123456");
		_config.db_name = iniparser_getstring(ini, "database:db", "cyj");
		_config.svr_port = iniparser_getint(ini, "server:port", 9090);
		
		_isloaded = true;
	}
	
	return true;
}

const st_env_config& Iniconfig::getconfig()
{
	return _config;
}
