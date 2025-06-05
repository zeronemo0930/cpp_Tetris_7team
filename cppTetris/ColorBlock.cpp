#include "ColorBlock.h"
#include "Board.h"

void ColorBlock::specialFunc(Board& board)
{
	int baseX = getX();        // 현재 블록 
	int baseY = getY() + 1;    // 아래쪽 기준
	colNum = board.board[baseY][baseX];
	for (size_t i = 0; i < Board::height - 1; i++) {
		for (size_t j = 1; j < Board::width - 1; j++) {
			if (board.board[i][j] == colNum) board.clear_cell(i, j);
		}
	}
	board.board[getY()][getX()] = 0;
}
