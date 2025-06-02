#pragma once
#include <iostream>
#include "Renderer.h"

class GameManager
{
private:
	short menuSelector;
	char keytemp;
	int isGameState;

	bool isHold;		// Hold 되어 있는 Block이 있는가?
	bool isNowHold;		// 지금 Hold 한 블럭인가?

	int score = 0;
	Board board;

	Block shadow_block;
	Block current_block;
	Block next_block;
	Block hold_block;

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
	void hold();

	void shadowBlock(bool isNew);
	void checkState();
	void makeNewBlock();
};

