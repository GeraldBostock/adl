#ifndef adl_scene_editor_h__
#define adl_scene_editor_h__

#include <string>

class adlScene_editor
{
public:
	adlScene_editor();
	~adlScene_editor();

	void update();
private:
	const std::string scene_files_path_ = "res/scenes/";
};

#endif // adl_scene_editor_h__