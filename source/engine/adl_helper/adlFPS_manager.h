#ifndef adl_fps_manager_h__
#define adl_fps_manager_h__

#include "adlTimer.h"
#include <vector>

#define FRAME_VALUES 10
#define MILLISECONDS_IN_SECOND 1000.0

class adlFPS_manager
{
public:
	adlFPS_manager(int target_fps, double report_interval = 2.0);
	~adlFPS_manager();

	float enforce_fps();
	float get_fps();

private:
	std::vector<float> frame_times_;

	adlTimer timer_;
	float frame_start_time_;
	float frame_end_time_;
	float frame_duration_;

	float target_fps_;                   
	int frame_count_;        

	float target_frame_duration_;
	float sleep_duration_;

	float last_report_time_;
	float report_interval_;
	
	float fps_;

	void init();
};

#endif // adl_fps_manager_h__