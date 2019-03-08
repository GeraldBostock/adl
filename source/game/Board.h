#ifndef board_h__
#define board_h__

#include "engine/adl_entities/adlEntity.h"
#include "Tetromino.h"

enum Directions
{
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

class Board
{
public:
	Board();
	~Board();

	void place_tetromino(Tetromino* tetromino);
	bool can_fit(Tetromino* tetromino, Directions direction);
	void check_and_resolve_full_line();
	int value_at(int i, int j)
	{
		if (board_[i][j] == nullptr)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	void debug_draw();

private:
	adlEntity_shared_ptr board_[14][25];

	std::vector<adlEntity_shared_ptr> discarded_entities_;
};

#endif //board_h__