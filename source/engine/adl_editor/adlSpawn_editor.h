#ifndef adlSpawn_editor_h__
#define adlSpawn_editor_h__  

#include "engine/adlScene_manager.h"

class adlSpawn_editor
{  
public:  
	adlSpawn_editor();
	~adlSpawn_editor();
 
	void init();
	void update(adlScene_manager* scene_manager);

	bool visible;

	adlTransform spawnTransform;

	adlModel_shared_ptr spawnModel;
	adlMaterial_shared_ptr spawnMaterial;

private:  
 
};  
 
#endif // adlSpawn_editor_h__  
 
