#include "FireBlock.h"
#include "Board.h"

void FireBlock::specialFunc(Board& board)
{
    int baseX = getX();        // ���� ��� 
    int baseY = getY() + 1;    // �Ʒ��� ����

    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            int x = baseX + dx;
            int y = baseY + dy;
            int w = baseX - dx;
            int z = baseY - dy;

            // ���� ���� ���� ���� ����, ���� ���� Ȯ��
            if (x >= 0 && x < Board::width &&
                y >= 0 && y < Board::height) {
                board.clear_cell(y, x);
            }
            if (w >= 0 && w < Board::width &&
                z >= 0 && z < Board::height) {
                board.clear_cell(z, w);
            }
            if (w >= 0 && w < Board::width &&
                y >= 0 && y < Board::height) {
                board.clear_cell(y, w);
            }
            if (x >= 0 && x < Board::width &&
                z >= 0 && z < Board::height) {
                board.clear_cell(z, x);
            }
        }
    }
    board.board[getY()][getX()] = 0;
}

