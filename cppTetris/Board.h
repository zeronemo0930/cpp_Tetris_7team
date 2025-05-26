#pragma once
class Board
{
public:
	int board[24][14];
	static const int width = 14;
	static const int height = 24;

	Board();

	void strike_check();
	void merge_block(Block block);
	void check_full_line();

};

