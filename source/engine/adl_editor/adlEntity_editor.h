#ifndef adlEntity_editor_h__
#define adlEntity_editor_h__  

#include "engine/adl_entities/adlEntity.h"

class adlEntity_editor 
{  
public:  
	adlEntity_editor();  
	~adlEntity_editor();  
 
	void update(std::vector<adlEntity_shared_ptr>& entities);
private:  
 
};  
 
#endif // adlEntity_editor_h__  
 
