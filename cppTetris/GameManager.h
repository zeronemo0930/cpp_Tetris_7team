#pragma once
#include <iostream>
#include "Renderer.h"
#include "SoundManager.h"
#include "Menu.h"

/*
* ��Ʈ������ ��� ������ҵ��� ��Ƽ� �����ϴ� Ŭ����
* �ϳ��� �ν��Ͻ��� �����Ͽ� ���
* 
* ���� GameManager Ŭ���������� ��Ʈ���� ���� Ŭ������ ��ü�� �����ϰ� �����Ѵ�.
* �ʿ��� ��ü�� �ִٸ�, ���ڸ� ���۷����� �����ͷ� �Ѱ� ����Ѵ�.
*/
class GameManager
{
private:
	
	char keytemp;
	int isGameState;

	int combo=0;
	int comboTimer = 0;

	bool isHold;		// Hold �Ǿ� �ִ� Block�� �ִ°�?
	bool isNowHold;		// ���� Hold �� ���ΰ�?

	int score = 0;

	// ���� �Ŵ��������� �����ϰ� ����ϴ� �ν��Ͻ���
	Menu menu;
	Board board;
	Renderer renderer;
	Monster monster;
	SoundManager sm;

	// �� ���� ���
	Tetromino randType;
	Block shadow_block;
	Block current_block;
	Block next_block;
	Block hold_block;

	void mainMenu();	// ���� �޴�
	void stage();		// stage ����
	void play();		// ���� ��ŸƮ

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
public:
	GameManager();
	~GameManager();

	// main.cpp���� ������ �� �ִ� �Լ�
	// ���� ���� �Լ�
	void start();

	
};

