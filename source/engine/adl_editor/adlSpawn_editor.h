#ifndef adl_spawn_editor_h__
#define adl_spawn_editor_h__  

#include "engine/adlScene_manager.h"

class adlSpawn_editor
{  
public:  
	adlSpawn_editor();
	~adlSpawn_editor();
 
	void init();
	void update(adlScene_manager* scene_manager);

	bool get_visible();

private:  
 
	bool is_visible_;

	adlTransform spawn_transform_;

	adlModel_shared_ptr spawn_model_;
	adlMaterial_shared_ptr spawn_material_;
};  
 
#endif // adl_spawn_editor_h__  
 
