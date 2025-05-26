#pragma once
#include <iostream>
#include <Windows.h>
#include "Block.h"
#include "Board.h"
enum class Color { // Color enum
	BLACK,      /*  0 : ��� */
	DARK_BLUE,    /*  1 : ��ο� �Ķ� */
	DARK_GREEN,    /*  2 : ��ο� �ʷ� */
	DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
	DARK_RED,    /*  4 : ��ο� ���� */
	DARK_VOILET,  /*  5 : ��ο� ���� */
	DARK_YELLOW,  /*  6 : ��ο� ��� */
	GRAY,      /*  7 : ȸ�� */
	DARK_GRAY,    /*  8 : ��ο� ȸ�� */
	BLUE,      /*  9 : �Ķ� */
	GREEN,      /* 10 : �ʷ� */
	SKY_BLUE,    /* 11 : �ϴ� */
	RED,      /* 12 : ���� */
	VOILET,      /* 13 : ���� */
	YELLOW,      /* 14 : ��� */
	WHITE,      /* 15 : �Ͼ� */
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