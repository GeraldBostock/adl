#include "engine/adl_helper/adlFPS_manager.h"

#include "engine/adl_debug/adlLogger.h"
#include "engine/adl_renderer/adlRender_manager.h"
#include "engine/adl_resource/adlResource_manager.h"

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
	frame_start_time_ = (timer_.get_elapsed_micro_seconds()) / 1000.0f;
	frame_end_time_ = frame_start_time_ + 1;
	frame_duration_ = 1;
	last_report_time_ = frame_start_time_;
	target_frame_duration_ = (1.0 / target_fps_) * MILLISECONDS_IN_SECOND;
	frame_times_.resize(FRAME_VALUES, 0);
	fps_ = target_fps_;
}

float adlFPS_manager::enforce_fps()
{
	//We maintain array of size FRAME_VALUES, this array stores frame times. These values are used to calculate an average fps.
	//Otherwise individual fps values can jump all over the place due to the way the OS services the program
	int frames_index = frame_count_ % FRAME_VALUES;

	frame_end_time_ = (timer_.get_elapsed_micro_seconds()) / 1000.0f;
	frame_duration_ = frame_end_time_ - frame_start_time_;

	sleep_duration_ = target_frame_duration_ - frame_duration_;

	if (sleep_duration_ > 0.0f)
	{
		//Sleep is not precise enough. We are working with microseconds here.
		//But doing it this way means cpu is at 100% even when its not doing anything.
		//Find a better way? ya wanker

		int64 time_to_sleep_in_microseconds = sleep_duration_ * 1000;
		float now = timer_.get_elapsed_micro_seconds();

		float target_time = now + time_to_sleep_in_microseconds;
		while (timer_.get_elapsed_micro_seconds() < target_time)
		{

		}
		
	}
	frame_start_time_ = (timer_.get_elapsed_micro_seconds()) / 1000.0f;

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

	float dt = frame_duration_ + (frame_start_time_ - frame_end_time_);

	frame_times_[frames_index] = dt;

	float frames_per_second = 0;
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

			fps_ = frames_per_second;
		}
	}

	//This 3 here is completely arbitrary. This is supposed to work if we are way over the time limit to complete one frame.
	//This can happen when program the is in the background for example. We are normalizing it when it happens so it doesnt muddy up
	//the dataset
	if (dt > target_frame_duration_ * 3)
	{
		dt = target_frame_duration_;
	}

	return dt;
}

float adlFPS_manager::get_fps()
{
	return fps_;
}