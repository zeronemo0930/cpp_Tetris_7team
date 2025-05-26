#pragma once
#include <iostream>
#include <Windows.h>
#include "Block.h"
#include "Board.h"
enum class Color{ // Color enum
	BLACK,      /*  0 : 까망 */
	DARK_BLUE,    /*  1 : 어두운 파랑 */
	DARK_GREEN,    /*  2 : 어두운 초록 */
	DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
	DARK_RED,    /*  4 : 어두운 빨강 */
	DARK_VOILET,  /*  5 : 어두운 보라 */
	DARK_YELLOW,  /*  6 : 어두운 노랑 */
	GRAY,      /*  7 : 회색 */
	DARK_GRAY,    /*  8 : 어두운 회색 */
	BLUE,      /*  9 : 파랑 */
	GREEN,      /* 10 : 초록 */
	SKY_BLUE,    /* 11 : 하늘 */
	RED,      /* 12 : 빨강 */
	VOILET,      /* 13 : 보라 */
	YELLOW,      /* 14 : 노랑 */
	WHITE,      /* 15 : 하양 */
};

class Renderer
{
public:
	void show_logo();

	int show_cur_block(int shapeIndex, int x, int y);
	int input_data();
	void drawBlock(Block& block);
	void eraseBlock(Block& block);


	void setBlockColor(Tetromino t);
	void drawBoard(Board& board);

	void eraseLine(Board& board);
private:
	Color color = Color::DARK_GRAY;
};