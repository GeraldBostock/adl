#ifndef adl_fps_manager_h__
#define adl_fps_manager_h__

#include "adlTimer.h"

class adlFPS_manager
{
public:
	adlFPS_manager(int target_fps, double report_interval = 2.0);
	~adlFPS_manager();

	double enforce_fps();
	float get_fps();

private:
	adlTimer timer_;
	double frame_start_time_;         
	double frame_end_time_;           
	double frame_duration_;          

	double target_fps_;           
	double fps_;          
	int frame_count_;        

	double target_frame_duration_;  
	double sleep_duration_;       

	double last_report_time_;
	double report_interval_;

	void init();
	//void set_target_fps();
};

#endif // adl_fps_manager_h__