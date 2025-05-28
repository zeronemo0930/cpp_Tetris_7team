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
			if (shape[i][j] != 1) continue; // ��� ���� �ƴ� ���

			int board_x = x + j;
			int board_y = y + i;

			// ���� ���� �� (��/��/��/��)
			if (board_x < 0 || board_x >= width ||
				board_y < 0 || board_y >= height)
				return true; 

			// �ٸ� ��ϰ��� �浹
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

void Board::rotate_shift(Block& b) // ȸ���� ������ ��쿡�� ������ ȸ�����ִ� �Լ�
{
	Block block = b; // parameter block�� ���� ���� ����
	block.rotate(); // ������ ���Ƿ� ȸ��
	const shapeVec& shape = block.getShape(); // ȸ���� ���� ����
	size_t size = shape.size(); // ������ �뷮
	while (block.getX() < 1 || block.getX() + size > 13) { // ������ board�� edge�� ������ �ִٸ�
		if (block.getX() < 1) // ���� edge�� �������� ��
			block.move(1, 0); // right shift
		else if(block.getX() + size > 13) //������ edge�� �������� ��
			block.move(-1, 0); // left shift
	}
	if (!strike_check(block)) /* ���� ���ǹ� false�� �ǹ� : shift �Ϸ� �Ŀ��� ������ board�� strike��
							  -> edge�� strike�� ���� �ƴ� ���� ��Ʈ���� ���������� �浹*/
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
