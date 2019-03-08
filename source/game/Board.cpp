#include "game/Board.h"

#include "engine/adlScene_manager.h"
#include "engine/adl_entities/adlTransform_component.h"
#include "engine/adl_renderer/adlDebug_renderer.h"
#include "engine/adl_entities/adlPhysics_component.h"

Board::Board()
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			board_[i][j] = nullptr;
		}
	}

	adlScene_manager* scene_manager = &adlScene_manager::get();

	for (int i = 0; i < 25; i++)
	{
		adlEntity_shared_ptr entity = scene_manager->add_entity_to_scene("wall");
		adlEntity_shared_ptr entity2 = scene_manager->add_entity_to_scene("wall");

		std::shared_ptr<adlTransform_component> trans_comp;
		if (entity->has_component("adlTransform_component"))
		{
			trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
			trans_comp->set_position(adlVec3(0, i * 2 + 20, 0));
		}

		std::shared_ptr<adlTransform_component> trans_comp2;
		if (entity2->has_component("adlTransform_component"))
		{
			trans_comp2 = std::shared_ptr<adlTransform_component>(entity2->get_component<adlTransform_component>("adlTransform_component"));
			trans_comp2->set_position(adlVec3(26, i * 2 + 20, 0));
		}

		board_[0][i] = entity;
		board_[13][i] = entity;
	}

	for (int i = 0; i < 14; i++)
	{
		adlEntity_shared_ptr entity = scene_manager->add_entity_to_scene("wall");
		std::shared_ptr<adlTransform_component> trans_comp;
		if (entity->has_component("adlTransform_component"))
		{
			trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
			trans_comp->set_position(adlVec3((i * 2), 20, 0));
		}
		board_[i][0] = entity;
	}
}

Board::~Board()
{
}


bool Board::can_fit(Tetromino* tetromino, Directions direction)
{
	int i = tetromino->get_current_i();
	int j = tetromino->get_current_j();

	if (direction == DIR_DOWN)
	{
		if (j == 0)
		{
			return false;
		}

		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				if (tetromino->get_entity_at(a, b) != nullptr && board_[i + b][j - 1 + a] != nullptr)
				{
					return false;
				}
			}
		}
	}

	if (direction == DIR_LEFT)
	{
		if (i == 0)
		{
			return false;
		}

		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				if (tetromino->get_entity_at(a, b) != nullptr && board_[i - 1 + b][j + a] != nullptr)
				{
					return false;
				}
			}
		}
	}

	if (direction == DIR_RIGHT)
	{
		if (i == 11)
		{
			return false;
		}

		for (int a = 0; a < 4; a++)
		{
			for (int b = 0; b < 4; b++)
			{
				if (tetromino->get_entity_at(a, b) != nullptr && board_[i + 1 + b][j + a] != nullptr)
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Board::place_tetromino(Tetromino* tetromino)
{
	int i = tetromino->get_current_i();
	int j = tetromino->get_current_j();

	for (int a = 0; a < 4; a++)
	{
		for (int b = 0; b < 4; b++)
		{
			if (tetromino->get_entity_at(a, b) != nullptr)
			{
				board_[i + b][j + a] = tetromino->get_entity_at(a, b);
			}
		}
	}
	check_and_resolve_full_line();
}

void Board::debug_draw()
{
	adlDebug_renderer* db_renderer = &adlDebug_renderer::get();

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (board_[i][j] != nullptr)
			{
				db_renderer->render_sphere(adlVec3(i * 2, j * 2 + 20, 0), adlColor::GREEN, 1);
			}
			else
			{
				db_renderer->render_sphere(adlVec3(i * 2, j * 2 + 20, 0), adlColor::BLUE, 1);
			}
		}
	}
}

void Board::check_and_resolve_full_line()
{
	std::vector<int> discarded_line_indices;
	for (int j = 1; j < 25; j++)
	{
		bool line_full = true;
		for (int i = 0; i < 14; i++)
		{
			if (board_[i][j] == nullptr)
			{
				line_full = false;
				break;
			}
		}

		if (line_full)
		{
			discarded_line_indices.insert(discarded_line_indices.begin(), j);
			for (int i = 1; i < 13; i++)
			{
				adlEntity_shared_ptr entity = board_[i][j];

				if (!entity->has_component("adlPhysics_component"))
				{
					adlEntity_factory* fac = &adlEntity_factory::get();
					fac->add_component_to_entity(entity, "adlPhysics_component");
					std::shared_ptr<adlPhysics_component> physics_comp  = std::shared_ptr<adlPhysics_component>(entity->get_component<adlPhysics_component>("adlPhysics_component"));
					physics_comp->apply_force(adlVec3(0, 0, -1), 100);
					discarded_entities_.push_back(entity);
				}
			}
		}
	}

	for (auto index : discarded_line_indices)
	{
		for (int i = 1; i < 13; i++)
		{
			board_[i][index] = nullptr;
		}
		for (int i = 1; i < 13; i++)
		{
			for (int j = index + 1; j < 25; j++)
			{
				adlEntity_shared_ptr entity = board_[i][j];
				if (entity)
				{
					std::shared_ptr<adlTransform_component> trans_comp;
					if (entity->has_component("adlTransform_component"))
					{
						trans_comp = std::shared_ptr<adlTransform_component>(entity->get_component<adlTransform_component>("adlTransform_component"));
						adlVec3 position = trans_comp->get_position();
						trans_comp->set_position(adlVec3(position.x, position.y - 2, position.z));
					}
					board_[i][j - 1] = entity;
					board_[i][j] = nullptr;
				}
			}
		}
	}
}