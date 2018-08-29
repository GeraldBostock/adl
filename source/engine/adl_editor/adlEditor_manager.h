#ifndef adl_editor_manager_h__
#define adl_editor_manager_h__

#include "adlLight_editor.h"
#include "adlActor_editor.h"

class adlEditor_manager
{
public:

	static adlEditor_manager& get()
	{
		static adlEditor_manager instance;
		return instance;
	}

	void update();

private:
	adlLight_editor* light_editor_;
	adlActor_editor* actor_editor_;

	bool light_editor_open_;
	bool actor_editor_open_;
	bool main_editor_open_;

	adlEditor_manager();
};

#endif // adl_editor_manager_h__