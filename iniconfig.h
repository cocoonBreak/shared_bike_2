#ifndef __SHBK_COMMON_INICONFIG_H__
#define __SHBK_COMMON_INICONFIG_H__

#include <string>
#include "configdef.h"

class Iniconfig{
public:
	Iniconfig();
	~Iniconfig();
	
	bool loadfile(const std::string& path);
	const st_env_config& getconfig();
	
private:
	st_env_config _config;
	bool _isloaded;
};

#endif
