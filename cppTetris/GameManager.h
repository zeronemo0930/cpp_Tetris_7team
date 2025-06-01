#pragma once
#include <iostream>
#include "Renderer.h"

class GameManager
{
private:
	short menuSelector;
	char keytemp;
	int isGameState;

	int score = 0;
	Board board;

	Block shadow_block;
	Block current_block;
	Block next_block;

	Renderer renderer;
	
	Tetromino randType;

	Monster monster;
public:
	GameManager();
	~GameManager();


	void start();
	void play();
	void menu();

	void init();
	void input();
	void update();

	void moveRotate();
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveSpace();

	void shadowBlock(bool isNew);
	void checkState();
	void makeNewBlock();
};

