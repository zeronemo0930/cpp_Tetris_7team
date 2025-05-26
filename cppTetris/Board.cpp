#include "Board.h"
#include "GameManager.h"


Board::Board()
{
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			if (i == 23 || j == 0 || j == 13) board[i][j] = 1;
			else board[i][j] = 0;
		}
	}
}

void Board::merge_block(Block& block)
{

}

int Board::check_full_line(Renderer& renderer)
{
	size_t i, j, k;
	for (i = 3; i < height - 1; i++)
	{
		for (j = 1; j < width - 1; j++)
		{
			if (total_block[i][j] == 0)
				break;
		}
		if (j == 13) {	//한줄이 다 채워졌음

			// 보드에서 줄 지우기
			for (k = i; k > 0; k--)
				for (j = 1; j < 13; j++)
					total_block[k][j] = total_block[k - 1][j];

			for (j = 1; j < 13; j++)
				total_block[0][j] = 0;

			return i;	// 지워진 줄 반환
		}
	}
	return -1;
}
