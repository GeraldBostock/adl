#ifndef adl_logger_h__
#define adl_logger_h__

#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON

#include "spdlog/spdlog.h"
#include <string>
#include <memory>

class adlLogger
{
public:
	static void log_error(const std::string& error, bool log_to_file = false);
	static void log_info(const std::string& info, bool log_to_file = false);

private:
	adlLogger();
	virtual ~adlLogger();

	static std::shared_ptr<spdlog::logger> info_logger_;
	static std::shared_ptr<spdlog::logger> error_logger_;
	static std::shared_ptr<spdlog::logger> console_;

	static bool init_;
};

#endif // adl_logger_h__