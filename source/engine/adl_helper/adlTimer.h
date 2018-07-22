#ifndef adl_timer_h__
#define adl_timer_h__

#include <chrono>
#include <ctime>

#include "common.h"

typedef std::chrono::time_point<std::chrono::system_clock> Time_point;
typedef std::chrono::system_clock Clock;

class adlTimer
{
public:
	adlTimer();
	~adlTimer();

	void start();
	void stop();
	double get_elapsed_milli_seconds();
	double get_elapsed_seconds();

private:
	Time_point start_time_;
	Time_point end_time_;
	bool is_paused_ = true;
};


#endif // adl_timer_h__