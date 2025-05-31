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
	Renderer();

	void show_logo();
	void show_menu(short menu);

	void drawBlock(Block& block);
	void eraseBlock(Block& block);


	void setBlockColor(Tetromino t);
	void drawBoard(Board& board);

	static void eraseLine(size_t i);
	//void show_next_block(Block& nextBlock);


private:
	Color color = Color::DARK_GRAY;
	std::array<std::string, 3> menu_string;
	int ab_x = 5;
	int ab_y = 1;
};

void gotoxy(int x, int y);
void SetColor(Color color);
