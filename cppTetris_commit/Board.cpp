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
bool Board::strike_check(const Block& b)
{
	const shapeVec& shape = b.getShape();
	size_t b_size = shape.size();
	int x = b.getX();
	int y = b.getY();

	for (int i = 0; i < b_size; ++i) {
		for (int j = 0; j < b_size; ++j) {
			if (shape[i][j] != 1) continue; // 블록 셀이 아닌 경우

			int board_x = x + j;
			int board_y = y + i;

			// 보드 범위 밖 (좌/우/상/하)
			if (board_x < 0 || board_x >= width ||
				board_y < 0 || board_y >= height)
				return true; 

			// 다른 블록과의 충돌
			if (board[board_y][board_x] == 1)
				return true;
		}
	}
	return false;
}


void Board::merge_block(Block& block)
{
	const shapeVec& shape = block.getShape();
	size_t b_size = shape.size();
	int x = block.getX();
	int y = block.getY();

	for (size_t i = 0; i < b_size; i++) {
		for (size_t j = 0; j < b_size; j++) {
			board[y + i][x + j] |= shape[i][j];
		}
	}
	for (size_t i = 3; i < height - 1; i++) {
		if (check_full_line(i)) {
			eraseBoardLine(i);
		}
	}
	
}

bool Board::check_full_line(size_t i)
{
	size_t j;
	for (j = 1; j < width - 1; j++) {
		if (board[i][j] == 0)
			break;
	}
	if (j == 13) 
		return true;
	
	return false;
}

int Board::eraseBoardLine(size_t i)
{
	for (size_t k = i; k > 0; k--)
	{
		for (size_t j = 1; j < 13; j++)
			board[k][j] = board[k - 1][j];
	}
	for (size_t j = 1; j < 13; j++)
		board[0][j] = 0;
	return 0;
}

void Board::rotate_shift(Block& b) // 회전이 가능한 경우에만 도형을 회전해주는 함수
{
	Block block = b; // parameter block에 대한 얕은 복사
	block.rotate(); // 도형을 임의로 회전
	const shapeVec& shape = block.getShape(); // 회전한 도형 정보
	size_t size = shape.size(); // 도형의 용량
	while (block.getX() < 1 || block.getX() + size > 13) { // 도형이 board의 edge에 걸쳐져 있다면
		if (block.getX() < 1) // 왼쪽 edge에 걸쳐있을 때
			block.move(1, 0); // right shift
		else if(block.getX() + size > 13) //오른쪽 edge에 걸쳐있을 때
			block.move(-1, 0); // left shift
	}
	if (!strike_check(block)) /* 다음 조건문 false의 의미 : shift 완료 후에도 도형이 board에 strike함
							  -> edge에 strike한 것이 아닌 쌓은 테트리스 도형끼리의 충돌*/
		b = block; //
}

int Board::move_block(Block& block)
{
	block.move(0, 1);
	if (strike_check(block)) {
		block.move(0, -1);
		if (block.getY() < 3)	return 1;	// GameOver
		merge_block(block);
		return 2;	// create new block
	}
	return 0;	// nothing
}
