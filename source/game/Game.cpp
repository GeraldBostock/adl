#include "Game.h"

#include <iostream>

#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_entities/adlRender_component.h"
#include "engine/adl_entities/adlPhysics_component.h"
#include "engine/adl_entities/adlPoint_light_component.h"
#include "engine/adl_entities/adlSun_component.h"
#include "game/Test_component.h"

#include <stdlib.h>
#include <time.h> 

Game::Game()
{

}

Game::~Game()
{

}


bool Game::init()
{
	srand(time(NULL));
	create_randomized_voxels();

	adlTransform_component tc;
	adlRender_component r;
	adlPhysics_component p;
	adlPoint_light_component l;
	adlSun_component sun;
	Test_component test_c;
	adlScene_shared_ptr scene = adl_scene_manager->create_empty_scene("new_scene");
	adl_scene_manager->set_active_scene(scene);

	scene->set_cube_map(adl_rm->get_cube_map("default"));
	
	listener_ = ADL_NEW(Physics_listener);
	adl_scene_manager->add_physics_observer(listener_);

	adlCamera* scene_camera = ADL_NEW(adlCamera);
	scene_camera->set_camera_type(ct_god_mode);
	scene_camera->init();
	scene_camera->set_pitch(-50);
	scene_camera->set_position(adlVec3(0, 30, 10));

	adl_scene_manager->set_camera(scene_camera);
	adl_scene_manager->set_sun(adl_scene_manager->add_entity_to_scene("sun_entity"));

	adl_window->set_mouse_visible(false);

	scene->set_camera(scene_camera);

	adlMaterial_shared_ptr copper = adl_rm->get_material("copper");

	adlTerrain_shared_ptr terrain = adl_rm->get_terrain("test_terrain");
	terrain->set_blend_map(adl_rm->get_texture("black"));
	terrain->set_texture_pack(adl_rm->get_texture_pack("default"));
	//adl_scene_manager->set_terrain(terrain);

	adlModel_shared_ptr box_model = adl_rm->get_model("Cube");
	//This works because the box model has only 1 mesh.
	adlMesh_shared_ptr box_mesh = box_model->get_all_meshes()[0];

	adlMesh_shared_ptr voxel_mesh = MAKE_SHARED(adlMesh);
	voxel_mesh->add_vertices(box_mesh->get_vertices(), box_mesh->get_indices());

	adlEntity_shared_ptr voxel_entity = adl_scene_manager->add_entity_to_scene("voxel_entity");

	int count = 0;

	std::vector<Vertex> transformed_mesh;
	transformed_mesh.resize(24 * voxels_.size());
	std::vector<unsigned int> indices;
	indices.resize(36 * voxels_.size());
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

		int vertex_index = 0;
		for (auto vertex : box_mesh->get_vertices())
		{
			adlVec3 pos = vertex.position;
			adlVec3 transformed_pos = transform.get_transformation_matrix().transform_to_parent(pos);
			transformed_mesh[i * 24 + vertex_index++] = Vertex(transformed_pos, vertex.normal, vertex.uv);
			vertex_count++;
			//transformed_mesh.push_back(Vertex(transformed_pos, vertex.normal, vertex.uv));
		}

		int voxel_mesh_vertex_count = voxel_mesh->get_vertex_count();
		const std::vector<unsigned int>& box_mesh_indices = box_mesh->get_indices();
		//std::vector<unsigned int> indices;
		for (unsigned int j = 0; j < box_mesh->get_index_count(); ++j)
		{
			indices[index_counter++] = box_mesh_indices[j] + vertex_count;
		}

		//voxel_mesh->add_vertices(transformed_mesh, indices);

		count++;

		if (count % 10000 == 0)
		{
			std::cout << count << std::endl;
		}
	}
	
	voxel_mesh->add_vertices(transformed_mesh, indices);

	voxel_mesh->set_texture(adl_rm->get_texture("grass"));
	voxel_mesh->set_material(adl_rm->get_material("copper"));

	adlModel_shared_ptr voxel_model = MAKE_SHARED(adlModel, "Voxels");
	voxel_model->add_mesh(voxel_mesh);
	voxel_model->set_material(adl_rm->get_material("copper"));
	//voxel_model->set_texture(adl_rm->get_texture("grass"));

	std::shared_ptr<adlRender_component> render_component = std::shared_ptr(voxel_entity->get_component<adlRender_component>("adlRender_component"));
	render_component->set_model(voxel_model);

	return true;
}

bool Game::update(float dt)
{
	if (adl_input->get_key_up(adl_key_escape))
	{
		return false;
	}

	if (adl_input->get_key(adl_key_left_alt) && adl_input->get_key_down(adl_key_f))
	{
		adl_window->toggle_fullscreen();
	}

	return true;
}

void Game::create_randomized_voxels()
{
	for (int i = 0; i < 200000; i++)
	{
		int x = rand() % 300;
		int y = rand() % 300;
		int z = rand() % 300;

		int size = rand() % 8;

		voxels_.push_back(Voxel(adlVec3(x, y, z), size));
	}
}
