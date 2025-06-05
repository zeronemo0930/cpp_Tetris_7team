#include "ColorBlock.h"
#include "Board.h"

void ColorBlock::specialFunc(Board& board)
{
	int baseX = getX();        // ���� ��� 
	int baseY = getY() + 1;    // �Ʒ��� ����
	colNum = board.board[baseY][baseX];
	for (size_t i = 0; i < Board::height - 1; i++) {
		for (size_t j = 1; j < Board::width - 1; j++) {
			if (board.board[i][j] == colNum) board.clear_cell(i, j);
		}
	}
	board.board[getY()][getX()] = 0;
}
