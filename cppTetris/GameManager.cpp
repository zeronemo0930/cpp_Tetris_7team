#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include "GameManager.h"

#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

using namespace std;

GameManager::GameManager():randType(Tetromino::I), keytemp(NULL), isGameState(0), menuSelector(0), monster(MonsterName::RAT), isHold(false)
{
	srand((unsigned int)time(NULL));
}

GameManager::~GameManager()
{

}

void GameManager::start()
{
	
	menu();
	if (menuSelector == 0) {
		play();
	} 
	else if (menuSelector == 1) {

	}
	else if (menuSelector == 2) {
		exit(0);
	}
}

void GameManager::play()
{

	// 테스트용 몬스터
	renderer.drawMonster(monster);
	renderer.drawMonsterHp(monster);

	
	init();
	int i = 0;
	score = 0;
	renderer.show_game_stat(score);
	while (true) {

		input();
		checkState();
		if (i % 30 == 0) {
			update();
		}

		i++;
		Sleep(15);
		gotoxy(77, 23);
	}
}

void GameManager::menu() {
	menuSelector = 0;
	renderer.show_logo();
	renderer.show_menu(menuSelector);
	while (keytemp != '\r') {

		if (_kbhit()) {
			keytemp = _getch();
			if (keytemp == EXT_KEY) {
				keytemp = _getch();
				switch (keytemp)
				{
				case KEY_UP:
					if (menuSelector > 0) {
						menuSelector--;
						renderer.show_menu(menuSelector);
					}
					break;
				case KEY_DOWN:
					if (menuSelector < 2) {
						menuSelector++;
						renderer.show_menu(menuSelector);
					}
					break;
				}
			}
		}
	}
	
	system("cls");
}

void GameManager::init()
{
	renderer.drawBoard(board);
	renderer.nextBlockFrame();
	renderer.holdBlockFrame();
	isHold = false;
	isGameState = 0;
	menuSelector = 0;
	randType = static_cast<Tetromino>(rand() % 7);
	current_block.setBlock(randType);
	current_block.setPos(5, 0);
	randType = static_cast<Tetromino>(rand() % 7);
	next_block.setBlock(randType);
	renderer.drawBlock(next_block, false);
	shadowBlock(true);
}

void GameManager::input()
{
	
	if (_kbhit()) {
		keytemp = _getch();
		if (keytemp == EXT_KEY) {
			keytemp = _getch();

			switch (keytemp) 
			{
			case KEY_UP:	// 회전
				moveRotate();
				break;

			case KEY_LEFT:	// 왼쪽으로 이동
				moveLeft();
				break;

			case KEY_RIGHT:	// 오른쪽으로 이동
				moveRight();
				break;

			case KEY_DOWN:	// 아래로 이동
				moveDown();
				break;
			}
		}
		if (keytemp == 32)	//스페이스바를 눌렀을때
		{
			moveSpace();
		}
		// HOLD 시키는 거
		else if (keytemp == 99 || keytemp == 67) {	// c, C를 입력 했을 때
			hold();
		}
	}
}

void GameManager::update()
{
	//renderer.drawBoard(board);
	renderer.eraseBlock(current_block);
	isGameState = board.move_block(current_block);

	renderer.drawBlock(current_block, false);
	checkState();
}

void GameManager::moveRotate()
{
	renderer.eraseBlock(current_block);
	board.rotate_shift(current_block); // rotate할 때 strike_check 여부를 확인하고 rotate 가능한 좌표로 변환해주는 rotate_shift
	shadowBlock(false);
	renderer.drawBlock(current_block, false);
}

void GameManager::moveLeft()
{
	renderer.eraseBlock(current_block);
	current_block.move(-1, 0);
	if (board.strike_check(current_block))
		current_block.move(1, 0);
	shadowBlock(false);
	renderer.drawBlock(current_block, false);
}

void GameManager::moveRight()
{
	if (current_block.getX() >= Board::width - 1) return;
	renderer.eraseBlock(current_block);
	current_block.move(1, 0);
	if (board.strike_check(current_block))
		current_block.move(-1, 0);
	shadowBlock(false);
	renderer.drawBlock(current_block, false);
}

void GameManager::moveDown()
{
	renderer.eraseBlock(current_block);
	isGameState = board.move_block(current_block);
	renderer.drawBlock(current_block, false);
}

void GameManager::moveSpace()
{
	renderer.eraseBlock(current_block);
	while (isGameState == 0) {
		isGameState = board.move_block(current_block);
	}

}

void GameManager::hold()
{
	if (isNowHold) return;
	if (!isHold) {
		Tetromino temp = current_block.getType();
		hold_block.setBlock(temp);
	
		makeNewBlock();
		isHold = true;
		
	}
	else{
		renderer.eraseBlock(hold_block);
		renderer.eraseBlock(current_block);
		Tetromino temp;
		temp = current_block.getType();
		current_block = hold_block;
		current_block.setPos(5, 0);

		hold_block.setBlock(temp);


		renderer.drawBlock(current_block, false);
		shadowBlock(false);
	}
	hold_block.setPos(-6, 1);
	isNowHold = true;
	renderer.drawBlock(hold_block, false);
}


void GameManager::shadowBlock(bool isNew)
{
	if(!isNew)
		renderer.eraseBlock(shadow_block);
	shadow_block = current_block;
	while (!board.strike_check(shadow_block)) {
		shadow_block.move(0, 1);
	}
	shadow_block.move(0, -1);
	renderer.drawBlock(shadow_block, true);
}

void GameManager::checkState()
{
	if (isGameState == 2) {
		// create New Block
		makeNewBlock();

		// 몬스터에 데미지가 들어가면 업데이트
		int temp = board.get_clear_line_score();
		if (temp != 0) {
			monster.takeDamage(temp / 100);

			// 테스트 용으로 넣어놓은 코드
			if (monster.isDead()) {
				renderer.drawMonsterHp(monster);
				exit(0);
			}
			renderer.drawMonsterHp(monster);
		}
		score += temp;
		renderer.show_game_stat(score);
	}
	else if (isGameState == 1) {
		if (monster.stage == 0) { monster.stage++; return; }                                                                 // 몬스터 죽으면 스테이지 업
		exit(0);
	}
	isGameState = 0;
}

void GameManager::makeNewBlock()
{
	renderer.drawBoard(board);
	renderer.eraseBlock(next_block);
	current_block = next_block;
	current_block.setPos(5, 0);
	randType = static_cast<Tetromino>(rand() % 7);
	next_block.setBlock(randType);
	renderer.drawBlock(next_block, false);
	shadowBlock(true);
	renderer.drawBlock(current_block, false);
	isNowHold = false;
}
