#pragma once
#include <iostream>
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
	DARK_YELLOW, 
	GRAY,    
	DARK_GRAY,  
	BLUE,     
	GREEN,   
	SKY_BLUE, 
	RED,     
	VOILET,   
	YELLOW, 
	WHITE,  
};

class Renderer
{
public:
	void show_logo();

	int input_data();
	void drawBlock(Block& block);
	void eraseBlock(Block& block);

	void show_next_block(Block& block);

	void show_game_stat(int score);

	void setBlockColor(Tetromino t);
	void drawBoard(Board& board);

	static void eraseLine(size_t i);


private:
	Color color = Color::DARK_GRAY;
	int ab_x = 5;
	int ab_y = 1;
};

void gotoxy(int x, int y);
void SetColor(Color color);
