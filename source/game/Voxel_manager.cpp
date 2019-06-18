#include "game/Voxel_manager.h"

#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlModel.h"

Voxel_manager::Voxel_manager()
{

}

Voxel_manager::~Voxel_manager()
{

}

void Voxel_manager::load_voxels()
{
	voxels_.push_back(Voxel(adlVec3(0, 0, 0), 1));
	voxels_.push_back(Voxel(adlVec3(0, 1, 0), 1));
	voxels_.push_back(Voxel(adlVec3(0, -1, 0), 1));
	voxels_.push_back(Voxel(adlVec3(0, 0, 1), 1));
	voxels_.push_back(Voxel(adlVec3(0, 0, -1), 1));
	voxels_.push_back(Voxel(adlVec3(1, 0, 0), 1));
	voxels_.push_back(Voxel(adlVec3(-1, 0, 0), 1));
}

adlMesh_shared_ptr Voxel_manager::create_voxel_mesh()
{
	adlResource_manager* adl_rm = &adlResource_manager::get();

	//Base model
	adlModel_shared_ptr box_model = adl_rm->get_model("Cube");
	//Base mesh
	adlMesh_shared_ptr box_mesh = box_model->get_all_meshes()[0];

	//Empty mesh. Will be filled with voxel vertices
	adlMesh_shared_ptr voxel_mesh = MAKE_SHARED(adlMesh);

	std::vector<Vertex> transformed_mesh;
	transformed_mesh.resize(box_mesh->get_vertex_count() * voxels_.size());
	std::vector<unsigned int> indices;
	indices.resize(box_mesh->get_index_count() * voxels_.size());
	int vertex_count = 0;
	int index_counter = 0;

	for (int i = 0; i < voxels_.size(); ++i)
	{
		Voxel voxel = voxels_[i];

		adlVec3 position = voxel.position;
		int size = voxel.size;

		adlMatrix_frame transform = adlMatrix_frame::identity();
		transform.o = position;
		transform.scale = adlVec3(size);
		adlMat4 trans_matrix = transform.get_transformation_matrix();

		int vertex_index = 0;
		for (auto vertex : box_mesh->get_vertices())
		{
			adlVec3 pos = vertex.position;
			adlVec3 transformed_pos = trans_matrix.transform_to_parent(pos);
			transformed_mesh[i * box_mesh->get_vertex_count() + vertex_index++] = Vertex(transformed_pos, vertex.normal, vertex.uv);
			vertex_count++;
		}

		int voxel_mesh_vertex_count = voxel_mesh->get_vertex_count();
		const std::vector<unsigned int>& box_mesh_indices = box_mesh->get_indices();
		for (unsigned int j = 0; j < box_mesh->get_index_count(); ++j)
		{
			indices[index_counter++] = box_mesh_indices[j] + vertex_count;
		}
	}

	voxel_mesh->add_vertices(transformed_mesh, indices);
	voxel_mesh->set_material(adl_rm->get_material("copper"));

	return voxel_mesh;
}