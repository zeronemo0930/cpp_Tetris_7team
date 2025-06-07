#pragma once
#include <iostream>
#include "Renderer.h"
#include "SoundManager.h"
#include "Menu.h"

/*
* 테트리스의 모든 구성요소들을 모아서 관리하는 클래스
* 하나의 인스턴스만 생성하여 사용
* 
* 오직 GameManager 클래스에서만 테트리스 관련 클래스의 객체를 생성하고 관리한다.
* 필요한 객체가 있다면, 인자를 레퍼런스나 포인터로 넘겨 사용한다.
*/
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

	// 게임 매니저에서만 선언하고 사용하는 인스턴스들
	Menu menu;
	Board board;
	Renderer renderer;
	Monster monster;
	SoundManager sm;

	// 블럭 관련 멤버
	Tetromino randType;
	Block shadow_block;
	Block current_block;
	Block next_block;
	Block hold_block;

	void mainMenu();	// 메인 메뉴
	void stage();		// stage 선택
	void play();		// 게임 스타트

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

	// main.cpp에서 실행할 수 있는 함수
	// 게임 시작 함수
	void start();

	
};

