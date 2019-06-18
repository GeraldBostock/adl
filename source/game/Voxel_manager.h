#ifndef voxel_manager_h__
#define voxel_manager_h__

#include <vector>

#include "engine/adl_math/adlVector.h"
#include "engine/adlShared_types.h"

struct Voxel
{
	adlVec3 position;
	int size;

	Voxel(const adlVec3& position, int size)
		: position(position),
		size(size)
	{

	}
};

class Voxel_manager
{
public:
	Voxel_manager();
	~Voxel_manager();

	void load_voxels();
	adlMesh_shared_ptr create_voxel_mesh();

private:
	std::vector<Voxel> voxels_;
};

#endif //voxel_manager_h__