#ifndef __DISTRIBUTED_LOGGER_H__
#define __DISTRIBUTED_LOGGER_H__

#include <string>
#include <log4cpp/Category.hh>

class logger{
public:
	~logger();
	bool init(const std::string& log_conf_file);
	
	static logger& get_instance()
	{
		return _instance;
	}
	
	log4cpp::Category* get_handle()
	{
		return _category;
	}

private:
	logger();

	static logger _instance;
	log4cpp::Category* _category;
};

#define LOG_INFO logger::get_instance().get_handle()->info
#define LOG_DEBUG logger::get_instance().get_handle()->debug
#define LOG_ERROR logger::get_instance().get_handle()->error
#define LOG_WARN logger::get_instance().get_handle()->warn

#endif