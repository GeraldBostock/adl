#ifndef adl_editor_manager_h__
#define adl_editor_manager_h__

#include "adlEntity_editor.h"
#include "adlSpawn_editor.h"
#include "adlScene_editor.h"

class adlEditor_manager
{
public:

	static adlEditor_manager& get()
	{
		static adlEditor_manager instance;
		return instance;
	}

	void clean_up();

	void update();

private:
	adlEntity_editor* entity_editor_;
	adlSpawn_editor* spawn_editor_;
	adlScene_editor* scene_editor_;


	bool main_editor_open_;
	bool entity_editor_open_;
	bool actor_editor_open_;
	bool light_editor_open_;
	bool help_open_;
	bool show_demo_window_;
	bool spawner_editor_open_;
	bool scene_editor_open_;

	bool was_mouse_visible_;

	adlEditor_manager();

	void MainMenu();
};

#endif // adl_editor_manager_h__