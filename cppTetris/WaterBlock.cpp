#include "WaterBlock.h"
#include "Board.h"

void WaterBlock::specialFunc(Board& board)
{
	for (size_t i = board.height - 2; i >= 0; i--) {
		for (size_t j = 1; j < board.width - 1; j++) {
			if (board.board[i + 1][j] == 0) {
				board.board[i + 1][j] = board.board[i][j];
				board.board[i][j] = 0;
			}
		}
	}
	board.board[getY()][getX()] = 0;
}
