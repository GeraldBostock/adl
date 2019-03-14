#ifndef adl_shared_types_h__
#define adl_shared_types_h__

#define MAKE_SHARED(Class_name, ...) std::make_shared<Class_name>(__VA_ARGS__)

class adlMesh;
class adlModel;
class adlStatic_shader;
class adlFont;
class adlEntity;
class adlMaterial;
class adlTexture;
class adlScene;
class adlTerrain;
class adlCube_map;
class adlEntity_component;

#include <memory>

typedef std::shared_ptr<adlMesh> adlMesh_shared_ptr;
typedef std::shared_ptr<adlModel> adlModel_shared_ptr;
typedef std::shared_ptr<adlStatic_shader> adlShader_shared_ptr;
typedef std::shared_ptr<adlFont> adlFont_shared_ptr;
typedef std::shared_ptr<adlEntity> adlEntity_shared_ptr;
typedef std::shared_ptr<adlMaterial> adlMaterial_shared_ptr;
typedef std::shared_ptr<adlTexture> adlTexture_shared_ptr;
typedef std::shared_ptr<adlScene> adlScene_shared_ptr;
typedef std::shared_ptr<adlTerrain> adlTerrain_shared_ptr;
typedef std::shared_ptr<adlCube_map> adlCube_map_shared_ptr;
typedef std::shared_ptr<adlEntity_component> adlEntity_component_shared_ptr;

typedef unsigned int adlEntity_id;
typedef unsigned int adlComponent_id;

#endif // adl_shared_types_h__