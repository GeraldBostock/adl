#ifndef adl_root_h__
#define adl_root_h__

class adlWindow;
class adlTimer;
class adlFPS_manager;

class adlRoot
{
public:
	adlRoot();
	~adlRoot();

	void run();
private:
	adlWindow* window_;
	adlFPS_manager* fps_manager_;
};


#endif // adl_root_h__