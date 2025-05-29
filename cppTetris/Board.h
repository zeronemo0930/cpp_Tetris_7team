#pragma once
#include "Block.h"

class Board
{
public:
	int board[24][14];
	static const int width = 14;
	static const int height = 24;

	Board();

	bool strike_check(const Block& b);
	void merge_block(Block& block);
	bool check_full_line(size_t i);
	int move_block(Block& block);
	int eraseBoardLine(size_t i);
	void rotate_shift(Block& b);
private:

};

