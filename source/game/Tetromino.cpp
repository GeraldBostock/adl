#include "Tetromino.h"

#include "engine/adl_entities/adlEntity_factory.h"
#include "engine/adlScene_manager.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_entities/adlRender_component.h"

Tetromino::Tetromino(Tetromino_type type)
{
	adlResource_manager* adl_rm = &adlResource_manager::get();
	adlMaterial_shared_ptr mat = nullptr;

	if (type == Tetromino_type::O)
	{
		int blocks[4][4] = {
					{0, 0, 0, 0},
					{0, 1, 1, 0},
					{0, 1, 1, 0},
					{0, 0, 0, 0}
		};
		mat = adl_rm->get_material("gold");
		init(blocks, mat);
	}
	if (type == Tetromino_type::I)
	{
		int blocks[4][4] = {
					{0, 1, 0, 0},
					{0, 1, 0, 0},
					{0, 1, 0, 0},
					{0, 1, 0, 0}
		};
		mat = adl_rm->get_material("bronze");
		init(blocks, mat);
	}
	if (type == Tetromino_type::S)
	{
		int blocks[4][4] = {
					{0, 1, 1, 0},
					{1, 1, 0, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0}
		};
		mat = adl_rm->get_material("ruby");
		init(blocks, mat);
	}
	if (type == Tetromino_type::Z)
	{
		int blocks[4][4] = {
					{0, 0, 0, 0},
					{0, 1, 1, 0},
					{0, 0, 1, 1},
					{0, 0, 0, 0}
		};
		mat = adl_rm->get_material("emerald");
		init(blocks, mat);
	}
	if (type == Tetromino_type::L)
	{
		int blocks[4][4] = {
					{0, 1, 0, 0},
					{0, 1, 0, 0},
					{0, 1, 1, 0},
					{0, 0, 0, 0}
		};
		mat = adl_rm->get_material("sapphire");
		init(blocks, mat);
	}
	if (type == Tetromino_type::J)
	{
		int blocks[4][4] = {
					{0, 0, 1, 0},
					{0, 0, 1, 0},
					{0, 1, 1, 0},
					{0, 0, 0, 0}
		};
		mat = adl_rm->get_material("white_plastic");
		init(blocks, mat);
	}
	if (type == Tetromino_type::T)
	{
		int blocks[4][4] = {
					{0, 1, 0, 0},
					{1, 1, 1, 0},
					{0, 0, 0, 0},
					{0, 0, 0, 0}
		};
		mat = adl_rm->get_material("silver");
		init(blocks, mat);
	}
}

void Tetromino::init(int blocks[][4], adlMaterial_shared_ptr mat)
{
	current_j_ = 22;
	current_i_ = 6;
	adlEntity_factory* factory = &adlEntity_factory::get();
	adlScene_manager* scene_manager = &adlScene_manager::get();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			blocks_[i][j] = blocks[i][j];
			if (blocks[i][j] == 1)
			{
				adlEntity_shared_ptr entity = scene_manager->add_entity_to_scene("test_entity");
				std::shared_ptr<adlTransform_component> trans_comp;
				if (entity->has_component("adlTransform_component"))
				{
					trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
					trans_comp->set_position(adlVec3((i + current_i_) * 2, (j + current_j_) * 2 + 20, 0));
					entities_[j][i] = entity;
				}
				std::shared_ptr<adlRender_component> render_comp;
				if (entity->has_component("adlRender_component"))
				{
					render_comp = std::shared_ptr<adlRender_component>(entity->get_component<adlRender_component>("adlRender_component"));
					render_comp->set_material(mat);
				}
			}
			else
			{
				entities_[j][i] = nullptr;
			}
		}
	}
}

Tetromino::~Tetromino()
{
	for (auto entity : entities_)
	{
		entity = nullptr;
	}
}

void Tetromino::move_down()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			adlEntity_shared_ptr entity = entities_[i][j];
			if (entity != nullptr)
			{
				std::shared_ptr<adlTransform_component> trans_comp;
				if (entity->has_component("adlTransform_component"))
				{
					trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
					adlVec3 position = trans_comp->get_position();
					trans_comp->set_position(adlVec3(position.x, position.y - 2, position.z));
				}
			}
		}
	}

	current_j_--;
}

void Tetromino::move_left()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			adlEntity_shared_ptr entity = entities_[i][j];
			if (entity != nullptr)
			{
				std::shared_ptr<adlTransform_component> trans_comp;
				if (entity->has_component("adlTransform_component"))
				{
					trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
					adlVec3 position = trans_comp->get_position();
					trans_comp->set_position(adlVec3(position.x - 2, position.y, position.z));
				}
			}
		}
	}

	current_i_--;
}

void Tetromino::move_right()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			adlEntity_shared_ptr entity = entities_[i][j];
			if (entity != nullptr)
			{
				std::shared_ptr<adlTransform_component> trans_comp;
				if (entity->has_component("adlTransform_component"))
				{
					trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
					adlVec3 position = trans_comp->get_position();
					trans_comp->set_position(adlVec3(position.x + 2, position.y, position.z));
				}
			}
		}
	}

	current_i_++;
}

int Tetromino::value_at(int i, int j)
{
	return blocks_[i][j];
}