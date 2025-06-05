#include "FireBlock.h"

void FireBlock::specialFunc(Board& board)
{
    int baseX = getX();        // 현재 블록 
    int baseY = getY() + 1;    // 아래쪽 기준

    for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
            int x = baseX + dx;
            int y = baseY + dy;

            // 보드 범위 안일 때만 삭제
            if (x >= 0 && x < board.width &&
                y >= 0 && y < board.height) {
                board.clear_cell(y, x);
            }
        }
    }
}

