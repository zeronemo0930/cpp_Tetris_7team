#pragma once
#include <iostream>
#include "Renderer.h"

class GameManager
{
private:
	short menuSelector;
	char keytemp;
	int isGameState;

	Board board;

	Block current_block;
	Block next_block;

	Renderer renderer;
	
	Tetromino randType;
public:
	GameManager();
	~GameManager();


	void start();
	void play();
	void menu();
	void init();
	void input();
	void update();

	void checkState();
	void makeNewBlock();
};

