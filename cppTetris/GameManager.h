#pragma once
#include <iostream>
#include "Renderer.h"
#include "SoundManager.h"
#include "Menu.h"


class GameManager
{
private:
	short menuSelector;
	short optionSelector;
	char keytemp;
	int isGameState;

	int difficulty;		// 0 : easy, 1 : normal, 2 : hard
	float volume;

	bool isHold;		// Hold �Ǿ� �ִ� Block�� �ִ°�?
	bool isNowHold;		// ���� Hold �� ���ΰ�?

	int score = 0;

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
	void play();
	void menu();
	void option();

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

