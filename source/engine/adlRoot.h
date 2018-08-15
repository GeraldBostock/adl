#ifndef adl_root_h__
#define adl_root_h__

#include <string>

#include "engine/common.h"
#include "engine/adl_renderer/adlCamera.h"
#include "engine/adl_renderer/adlColor.h"

class adlWindow;
class adlTimer;
class adlFPS_manager;
class adlResource_manager;
class adlInput;
class adlRender_manager;
class adlLogger;

/*
* Entry point for the engine
* Extend this class and implement init() and update(double dt) methods
*/
class adlRoot
{
public:
	adlRoot();
	~adlRoot();
	
	void start();
	virtual bool init() = 0;
	virtual bool update(int64 dt) = 0;
	void run();

protected:
	adlResource_manager* adl_rm;
	adlRender_manager* adl_renderer;
	adlInput* adl_input;
	adlLogger* adl_logger;
	adlWindow* window_;
	adlCamera* camera;

	void init_window(const std::string& title, int width, int height);
private:
	adlFPS_manager* fps_manager_;

	bool is_running_;

	void game_thread();
};


#endif // adl_root_h__