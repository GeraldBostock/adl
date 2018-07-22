#ifndef adl_shared_types_h__
#define adl_shared_types_h__

class adlMesh;
class adlModel;

#include <memory>

typedef std::shared_ptr<adlMesh> adlMesh_shared_ptr;
typedef std::shared_ptr<adlModel> adlModel_shared_ptr;

#endif // adl_shared_types_h__