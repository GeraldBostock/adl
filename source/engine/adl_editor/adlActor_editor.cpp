#include "adlActor_editor.h"
#include "engine/adl_debug/imgui/imgui.h"


adlActor_editor::adlActor_editor()
{
}


adlActor_editor::~adlActor_editor()
{
}

void adlActor_editor::update(std::vector<adlActor_shared_ptr>& actors)
{
	ImGui::Begin("Actor Editor");
	ImGui::End();
}
