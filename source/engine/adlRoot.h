#ifndef adl_root_h__
#define adl_root_h__

#include <string>

class adlWindow;
class adlTimer;
class adlFPS_manager;
class adlResource_manager;
class adlInput;

class adlRoot
{
public:
	adlRoot();
	~adlRoot();
	
	void start();
	virtual bool init() = 0;
	virtual bool update(double dt) = 0;
	void run();

protected:
	adlResource_manager* adl_rm;
	adlInput* adl_input;

	void init_window(const std::string& title, int width, int height);
private:
	adlWindow* window_;
	adlFPS_manager* fps_manager_;

	bool is_running_;

	void game_thread();
};


#endif // adl_root_h__