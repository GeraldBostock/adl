#ifndef adl_editor_manager_h__
#define adl_editor_manager_h__

#include "adlEntity_editor.h"
#include "adlActor_editor.h"
#include "adlLight_editor.h"

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
	adlActor_editor* actor_editor_;
	adlLight_editor* light_editor_;

	bool main_editor_open_;
	bool entity_editor_open_;
	bool actor_editor_open_;
	bool light_editor_open_;
	bool help_open_;
	bool show_demo_window_;

	bool spawner_editor_open_;

	adlEditor_manager();

	void MainMenu();
};

#endif // adl_editor_manager_h__