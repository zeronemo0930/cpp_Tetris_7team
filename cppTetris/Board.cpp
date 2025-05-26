
#include "Board.h"


Board::Board()
{
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			if (i == 23 || j == 0 || j == 13) board[i][j] = 1;
			else board[i][j] = 0;
		}
	}
}
//I, O, T, J, L, S, Z
bool Board::strike_check(Block b)
{
	int b_size = b.getShape().size();
	bool wall_hit = false;
	bool floor_hit = false;
	for (int i = 0; i < b_size; i++) {
		for (int j = 0; j < b_size; j++) {
			if (b.getX() + j == 0 || b.getX() + j == 13)
				wall_hit = true;
			else
				wall_hit = (board[b.getY() + i][b.getX() + j] == 1);
			floor_hit = (b.getShape()[i][j] == 1);
			if (wall_hit && floor_hit) {
				return true;
			}
		}
	}
	return false;
}

void Board::merge_block(Block block)
{

}

void Board::check_full_line()
{
}

int Board::move_block(Block& b1, Block& b2)
{
	b1.setY(1);
	if (strike_check(b1)) {
		if (b1.getY() < 4) {
			return 1;
		}
		merge_block(b1);
		return 2;
	}
	return 0;
}
