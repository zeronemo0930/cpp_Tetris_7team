#include "ColorBlock.h"

void ColorBlock::specialFunc(Board& board)
{
	int baseX = getX();        // ���� ��� 
	int baseY = getY() + 1;    // �Ʒ��� ����
	colNum = board[baseY][baseX];
	for (size_t i = 0; i < board.height - 1; i++) {
		for (size_t j = 1; j < board.width - 1; j++) {
			if (board[i][j] == colNum) board.clear_cell(i.j);
		}
	}
}
