#pragma once
#include <iostream>
#include "Renderer.h"

class GameManager
{
private:
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


	void play();

	void init();
	void input();
	void update();

	void checkState();
};

