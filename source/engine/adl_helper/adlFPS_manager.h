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

	double enforce_fps();
	float get_fps();

private:
	std::vector<double> frame_times_;

	adlTimer timer_;
	double frame_start_time_;         
	double frame_end_time_;           
	double frame_duration_;          

	double target_fps_;                   
	int frame_count_;        

	double target_frame_duration_;  
	double sleep_duration_;       

	double last_report_time_;
	double report_interval_;

	void init();
};

#endif // adl_fps_manager_h__