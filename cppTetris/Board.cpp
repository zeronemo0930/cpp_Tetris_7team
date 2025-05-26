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

void Board::merge_block(Block block)
{

}

void Board::check_full_line()
{
}
