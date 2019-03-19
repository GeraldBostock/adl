#ifndef adl_resource_manager_editor_h__
#define adl_resource_manager_editor_h__

#include "engine/adl_debug/imgui/imgui.h"

class adlResource_manager_editor
{
public:
	adlResource_manager_editor();
	~adlResource_manager_editor();

	void update();

private:
	ImVec4 loaded_color_;
	ImVec4 not_loaded_color_;
};

#endif //adl_resource_manager_editor_h__