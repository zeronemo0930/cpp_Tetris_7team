#pragma once
#include "Block.h"
#include "ColorBlock.h"
#include "FireBlock.h"
#include "WaterBlock.h"

class Board
{
public:
	int lastScore = 0;

	int board[24][14];
	static const int width = 14;
	static const int height = 24;
	static inline int limit = 0; // ������ ������ ���� �� �����ϴ� key

	Board();
	void clear_cell(int y, int x) { board[y][x] = 0; }
	bool strike_check(const Block& b);
	void merge_block(Block& block);
	bool check_full_line(size_t i);
	int get_clear_line_score();
	int move_block(Block& block);
	int eraseBoardLine(size_t i);

	void resetBoard();	// ���忡 �ִ� ��� ���� �����ϴ� �Լ�

  bool rotate_shift(Block& b);
	void result_by_attack(const int empty_place);
private:

};

