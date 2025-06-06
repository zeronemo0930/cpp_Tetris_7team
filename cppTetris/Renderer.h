#pragma once
#include <iostream>
#include <array>
#include <Windows.h>
#include <vector>
#include "Block.h"
#include "Board.h"
#include "Monster.h"
#include <iomanip>
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

	// 메뉴 관련 Renderer
	void show_logo();
	void show_menu(short menu);
	void drawOption(short optionSelector, float volume, int difficulty);
	void drawStageSelect(short stageSelector);

	// Block 관련 Renderer
	void drawBlock(Block& block, bool isShadow);
	void eraseBlock(Block& block);
	void setBlockColor(Tetromino t);
	void nextBlockFrame();
	void holdBlockFrame();

	
	// Board 관련 Renderer
	void drawBoard(Board& board);
	void show_game_stat(int score);

	static void eraseLine(size_t i);

	// Monster 관련 Renderer
	void drawMonster(Monster& mon);
	void drawMonsterTalk(Monster& mon);
	void drawMonsterHp(Monster& mon);
	void aniMonsterDamaged(Monster& mon);
	void eraseMonster(Monster& mon);
	void act_by_boss(Monster& mon, Board& board);

	// 대화창 관련 Renderer
	void printLineAt(int x, int y, std::vector<std::string> lines);
	void printLineProlog(int x, int y, std::vector<std::string> lines);
private:
	Color color = Color::DARK_GRAY;
	std::array<std::string, 3> menu_string;
	std::array<std::string, 3> option_string;
	std::array<std::string, 3> difficulty_string;
	std::array<std::string, 7> stage_string;
	int ab_x = 14;
	int ab_y = 1;
};

void gotoxy(int x, int y);
void SetColor(Color color);
