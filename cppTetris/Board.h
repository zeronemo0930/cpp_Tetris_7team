#pragma once
#include "Block.h"

class Board
{
public:
	int board[24][14];
	static const int width = 14;
	static const int height = 24;

	Board();
	bool strike_check(Block b);
};

