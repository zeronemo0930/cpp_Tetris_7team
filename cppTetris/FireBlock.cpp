#include "FireBlock.h"

void FireBlock::specialFunc(Board& board)
{
    int baseX = getX();        // ���� ��� 
    int baseY = getY() + 1;    // �Ʒ��� ����

    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            int x = baseX + dx;
            int y = baseY + dy;

            // ���� ���� ���� ���� ����
            if (x >= 0 && x < board.width &&
                y >= 0 && y < board.height) {
                board.clear_cell(y, x);
            }
        }
    }
}

