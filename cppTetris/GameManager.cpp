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

GameManager::GameManager():randType(Tetromino::I), keytemp(NULL), isGameState(0), menuSelector(0)
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
	renderer.drawBoard(board);
	init();
	int i = 0;
	while (true) {
		input();
		checkState();
		if (i % 30 == 0)
			update();
		i++;
		Sleep(15);
		gotoxy(77, 23);
	}
}

void GameManager::menu() {
	menuSelector = 0;
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
	isGameState = 0;
	menuSelector = 0;
	randType = static_cast<Tetromino>(rand() % 7);
	current_block.setBlock(randType);
	current_block.setPos(5, 0);
	randType = static_cast<Tetromino>(rand() % 7);
	next_block.setBlock(randType);
	renderer.drawBlock(next_block);
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
				renderer.eraseBlock(current_block);
				board.rotate_shift(current_block); // rotate할 때 strike_check 여부를 확인하고 rotate 가능한 좌표로 변환해주는 rotate_shift
				//current_block.rotate();
				renderer.drawBlock(current_block);
				break;

			case KEY_LEFT:	// 왼쪽으로 이동
				//if (current_block.getX() <= 1) break;
				renderer.eraseBlock(current_block);
				current_block.move(-1, 0);
				if (board.strike_check(current_block)) 
					current_block.move(1, 0);
				renderer.drawBlock(current_block);
				break;

			case KEY_RIGHT:	// 오른쪽으로 이동
				if (current_block.getX() >= Board::width-1) break;
				renderer.eraseBlock(current_block);
				current_block.move(1, 0);
				if (board.strike_check(current_block))
					current_block.move(-1, 0);
				renderer.drawBlock(current_block);
				break;

			case KEY_DOWN:	// 아래로 이동
				renderer.eraseBlock(current_block);
				isGameState = board.move_block(current_block);
				renderer.drawBlock(current_block);
				break;
			}
		}
		if (keytemp == 32)	//스페이스바를 눌렀을때
		{
			renderer.eraseBlock(current_block);
			while (isGameState == 0) {
				isGameState = board.move_block(current_block);
			}
			//renderer.drawBoard(board);
		}
	}
}

void GameManager::update()
{
	//renderer.drawBoard(board);
	renderer.eraseBlock(current_block);
	isGameState = board.move_block(current_block);
	renderer.drawBlock(current_block);
	checkState();
}

void GameManager::checkState()
{
	if (isGameState == 2) {
		// create New Block
		makeNewBlock();
	}
	else if (isGameState == 1) {
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
	renderer.drawBlock(next_block);
}
