#include "engine/adl_helper/adlTimer.h"

adlTimer::adlTimer()
{

}

adlTimer::~adlTimer()
{

}

void adlTimer::start()
{
	start_time_ = Clock::now();
	is_paused_ = false;
}

void adlTimer::stop()
{
	end_time_ = Clock::now();
	is_paused_ = true;
}

double adlTimer::get_elapsed_milli_seconds()
{
	Time_point end_time;

	if (!is_paused_)
	{
		end_time = Clock::now();
	}
	else
	{
		end_time = end_time_;
	}

	return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_).count();
}

double adlTimer::get_elapsed_seconds()
{
	return get_elapsed_milli_seconds() / 1000.0;
}