#include "adlEntity_editor.h" 
#include "engine/adl_debug/imgui/imgui.h"

 
adlEntity_editor::adlEntity_editor() {  
 
}  
 
adlEntity_editor::~adlEntity_editor() {  
 
}

void adlEntity_editor::update(std::vector<adlEntity_shared_ptr>& entities)
{
	ImGui::Begin("Entity Editor");
	ImGui::Text("Entities\n");
	ImGui::End();
}
