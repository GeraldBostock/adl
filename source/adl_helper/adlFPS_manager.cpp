#include "adl_helper/adlFPS_manager.h"

#include "adl_debug/adlLogger.h"

#include <thread>
#include <chrono>

adlFPS_manager::adlFPS_manager(int target_fps, double report_interval)
	: target_fps_(target_fps),
	  report_interval_(report_interval)
{
	init();
}

adlFPS_manager::~adlFPS_manager()
{

}

void adlFPS_manager::init()
{
	timer_.start();
	frame_count_ = 0;
	fps_ = 0.0;
	sleep_duration_ = 0.0;
	frame_start_time_ = timer_.get_elapsed_milli_seconds();
	frame_end_time_ = frame_start_time_ + 1;
	frame_duration_ = 1;
	last_report_time_ = frame_start_time_;
	target_frame_duration_ = (1.0 / target_fps_) * 1000;
}

double adlFPS_manager::enforce_fps()
{
	frame_end_time_ = timer_.get_elapsed_milli_seconds();
	frame_duration_ = frame_end_time_ - frame_start_time_;

	if (report_interval_ != 0.0f)
	{
		if ((frame_end_time_ - last_report_time_) > report_interval_ * 1000)
		{
			last_report_time_ = frame_end_time_;

			fps_ = (double)frame_count_ / timer_.get_elapsed_milli_seconds() * 1000;

			adlLogger::log_info("FPS: " + std::to_string(fps_));
		}
	}
	sleep_duration_ = target_frame_duration_ - frame_duration_;

	if (sleep_duration_ > 0.0)
	{
		const unsigned long time_to_sleep = static_cast<unsigned long>(sleep_duration_);
		std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
	}
	frame_start_time_ = timer_.get_elapsed_milli_seconds();
	frame_count_++;

	return (frame_duration_ + (frame_start_time_ - frame_end_time_));
}

float adlFPS_manager::get_fps()
{
	return fps_;
}