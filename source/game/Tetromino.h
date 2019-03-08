#ifndef tetromino_h__
#define tetromino_h__

#include "engine/adl_entities/adlEntity.h"
#include "engine/adl_resource/adlResource_manager.h"
#include "engine/adl_resource/adlMaterial.h"

#include <vector>

enum Tetromino_type
{
	O,
	I,
	S,
	Z,
	L,
	J,
	T
};

class Tetromino
{
public:
	Tetromino(Tetromino_type type);
	~Tetromino();

	void move_down();
	void move_left();
	void move_right();
	int value_at(int i, int j);
	void destroy()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				entities_[i][j] = nullptr;
			}
		}
	}

	int get_current_i()
	{
		return current_i_;
	}

	int get_current_j()
	{
		return current_j_;
	}

	adlEntity_shared_ptr get_entity_at(int i, int j)
	{
		return entities_[i][j];
	}

private:
	//std::vector<adlEntity_shared_ptr> entities_;
	adlEntity_shared_ptr entities_[4][4];
	int blocks_[4][4];
	int current_i_;
	int current_j_;

	void init(int blocks[][4], adlMaterial_shared_ptr mat);
};

#endif //tetromino_h__