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

	bool scene_chooser_open_ = false;
	bool scene_saver_open_ = false;

	void save_scene(const char* scene_name);
};

#endif // adl_scene_editor_h__