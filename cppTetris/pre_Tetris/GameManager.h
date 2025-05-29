#pragma once
#include <iostream>
#include "Renderer.h"
#include "Board.h"



class GameManager
{
private:

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
	void make_new_block();
};

