#include "engine/adl_helper/adlFPS_manager.h"

#include "engine/adl_debug/adlLogger.h"
#include <SDL2/SDL.h>

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
	sleep_duration_ = 0.0;
	frame_start_time_ = timer_.get_elapsed_milli_seconds();
	frame_end_time_ = frame_start_time_ + 1;
	frame_duration_ = 1;
	last_report_time_ = frame_start_time_;
	target_frame_duration_ = (1.0 / target_fps_) * MILLISECONDS_IN_SECOND;
	frame_times_.resize(FRAME_VALUES, 0);
}

double adlFPS_manager::enforce_fps()
{
	int frames_index = frame_count_ % FRAME_VALUES;

	frame_end_time_ = timer_.get_elapsed_milli_seconds();
	frame_duration_ = frame_end_time_ - frame_start_time_;

	sleep_duration_ = target_frame_duration_ - frame_duration_;

	if (sleep_duration_ > 0.0)
	{
		//TODO find a better way of doing this
		const unsigned long time_to_sleep = static_cast<unsigned long>(sleep_duration_);
		SDL_Delay(time_to_sleep);
		//std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
	}
	frame_start_time_ = timer_.get_elapsed_milli_seconds();

	frame_count_++;

	int count;
	if (frame_count_ < FRAME_VALUES)
	{
		count = frame_count_;
	}
	else
	{
		count = FRAME_VALUES;
	}

	double dt = frame_duration_ + (frame_start_time_ - frame_end_time_);

	frame_times_[frames_index] = dt;

	double frames_per_second = 0;
	for (int i = 0; i < count; i++)
	{
		frames_per_second += frame_times_[i];
	}

	frames_per_second /= count;
	frames_per_second = MILLISECONDS_IN_SECOND / frames_per_second;

	if (report_interval_ != 0.0f)
	{
		if ((frame_end_time_ - last_report_time_) > report_interval_ * MILLISECONDS_IN_SECOND)
		{
			last_report_time_ = frame_end_time_;

			
			adlLogger* adl_logger = &adlLogger::get();
			adl_logger->log_info("FPS:" + std::to_string(frames_per_second));
		}
	}

	return dt;
}