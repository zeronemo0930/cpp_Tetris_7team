#pragma once
#include <iostream>
#include "Renderer.h"
#include "SoundManager.h"

class GameManager
{
private:
	char keytemp;
	int isGameState;
	Board board;

	int score = 0;

	Block current_block;
	Block next_block;

	SoundManager sound;

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