#pragma once
#include <iostream>
#include <array>
#include <Windows.h>
#include "Block.h"
#include "Board.h"

enum class Color{
	BLACK,
	DARK_BLUE, 
	DARK_GREEN, 
	DARK_SKY_BLUE, 
	DARK_RED, 
	DARK_VOILET, 
	DARK_YELLOW,		// Tetris L Block
	GRAY,    
	DARK_GRAY,			
	BLUE,				// Tetris J Block
	GREEN,				// Tetris S Block
	SKY_BLUE,			// Tetris I Block
	RED,				// Tetris Z Block
	VOILET,				// Tetris T Block
	YELLOW,				// Tetris O Block
	WHITE,  
};

class Renderer
{
public:
	Renderer();

	void show_logo();
	void show_menu(short menu);

	void drawBlock(Block& block, bool isShadow);
	void eraseBlock(Block& block);

	void setBlockColor(Tetromino t);
	void drawBoard(Board& board);

	static void eraseLine(size_t i);

	void show_game_stat(int score);

	void setBoardBlockColor(Tetromino t);
	//void show_next_block(Block& nextBlock);


private:
	Color color = Color::DARK_GRAY;
	std::array<std::string, 3> menu_string;
	int ab_x = 5;
	int ab_y = 1;
};

void gotoxy(int x, int y);
void SetColor(Color color);
