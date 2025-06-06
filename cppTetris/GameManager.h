#pragma once
#include <iostream>
#include "Renderer.h"
#include "SoundManager.h"
#include "Menu.h"


class GameManager
{
private:
	
	char keytemp;
	int isGameState;

	int combo=0;
	int comboTimer = 0;

	bool isHold;		// Hold 되어 있는 Block이 있는가?
	bool isNowHold;		// 지금 Hold 한 블럭인가?

	int score = 0;

	Menu menu;

	Board board;

	Block shadow_block;
	Block current_block;
	Block next_block;
	Block hold_block;

	Renderer renderer;
	
	Tetromino randType;

	Monster monster;

	SoundManager sm;
public:
	GameManager();
	~GameManager();


	void start();

	void mainMenu();
	void play();


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
	bool checkState();
	void makeNewBlock();
};

