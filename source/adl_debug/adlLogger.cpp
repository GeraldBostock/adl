#include "adlLogger.h"

bool adlLogger::init_ = false;
std::shared_ptr<spdlog::logger> adlLogger::info_logger_ = spdlog::basic_logger_mt("info_logger", "../logs/info.log");
std::shared_ptr<spdlog::logger> adlLogger::error_logger_ = spdlog::basic_logger_mt("error_logger", "../logs/error.log");
std::shared_ptr<spdlog::logger> adlLogger::console_ = spdlog::stderr_color_mt("console");

adlLogger::adlLogger()
{
}

adlLogger::~adlLogger()
{
}

void adlLogger::log_error(const std::string& error, bool log_to_file)
{
	console_->error(error);
	if(log_to_file)
	{
		error_logger_->info(error);
	}
}

void adlLogger::log_info(const std::string& info, bool log_to_file)
{
	console_->info(info);
	if (log_to_file)
	{
		info_logger_->info(info);
	}
}