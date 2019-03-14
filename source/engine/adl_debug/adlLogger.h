#ifndef adl_logger_h__
#define adl_logger_h__

#pragma warning(push, 0)
#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON

#include <spdlog.h>
#pragma warning(pop)

#include <string>
#include <memory>

#include "engine/adl_math/adlVector.h"

class adlLogger
{
public:
	static adlLogger& get()
	{
		static adlLogger instance;
		return instance;
	}

	void log_error(const std::string& error, bool log_to_file = false);
	void log_info(const std::string& info, bool log_to_file = false);
	void log_warning(const std::string& warning, bool log_to_file = false);
	void log_info(const std::string& vector_name, adlVec3& vector, bool log_to_file = false);

private:
	adlLogger();
	virtual ~adlLogger();

	std::shared_ptr<spdlog::logger> info_logger_= spdlog::basic_logger_mt("info_logger", "../logs/info.log");
	std::shared_ptr<spdlog::logger> error_logger_= spdlog::basic_logger_mt("error_logger", "../logs/error.log");
	std::shared_ptr<spdlog::logger> warning_logger_ = spdlog::basic_logger_mt("warning_logger", "../logs/warning.log");
	std::shared_ptr<spdlog::logger> console_ = spdlog::stderr_color_mt("console");

	bool init_ = false;
};

#endif // adl_logger_h__