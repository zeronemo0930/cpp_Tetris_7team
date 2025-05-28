#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include "GameManager.h"

#define EXT_KEY			0xffffffe0	//Ȯ��Ű �νİ� 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

using namespace std;

GameManager::GameManager():randType(Tetromino::I), keytemp(NULL), isGameState(0)
{
	srand((unsigned int)time(NULL));
}

GameManager::~GameManager()
{

}

void GameManager::play()
{

	renderer.show_logo();
	renderer.input_data();
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

void GameManager::init()
{
	randType = static_cast<Tetromino>(rand() % 7);
	current_block.setBlock(randType);
	randType = static_cast<Tetromino>(rand() % 7);
	next_block.setBlock(randType);
}

void GameManager::input()
{
	
	if (_kbhit()) {
		keytemp = _getch();
		if (keytemp == EXT_KEY) {
			keytemp = _getch();

			switch (keytemp) 
			{
			case KEY_UP:	// ȸ��
				renderer.eraseBlock(current_block);
				board.rotate_shift(current_block); // rotate�� �� strike_check ���θ� Ȯ���ϰ� rotate ������ ��ǥ�� ��ȯ���ִ� rotate_shift
				//current_block.rotate();
				renderer.drawBlock(current_block);
				break;
			case KEY_LEFT:	// �������� �̵�
				//if (current_block.getX() < 1) break;
				renderer.eraseBlock(current_block);
				current_block.move(-1, 0);
				if (board.strike_check(current_block)) 
					current_block.move(1, 0);
				renderer.drawBlock(current_block);
				break;
			case KEY_RIGHT:	// ���������� �̵�
				if (current_block.getX() >= Board::width-1) break;
				renderer.eraseBlock(current_block);
				current_block.move(1, 0);
				if (board.strike_check(current_block))
					current_block.move(-1, 0);
				renderer.drawBlock(current_block);
				
				break;
			case KEY_DOWN:	// �Ʒ��� �̵�
				renderer.eraseBlock(current_block);
				isGameState = board.move_block(current_block);
				renderer.drawBlock(current_block);
				//renderer.drawBoard(board);
				break;
			}
		}
		if (keytemp == 32)	//�����̽��ٸ� ��������
		{
			renderer.eraseBlock(current_block);
			while (isGameState == 0) {
				isGameState = board.move_block(current_block);
			}
			renderer.drawBlock(current_block);
			renderer.drawBoard(board);
		}
	}
}

void GameManager::update()
{
	renderer.drawBoard(board);
	renderer.eraseBlock(current_block);
	isGameState = board.move_block(current_block);
	renderer.drawBlock(current_block);
	checkState();
}

void GameManager::checkState()
{
	if (isGameState == 2) {
		// create New Block
		current_block = next_block;
		randType = static_cast<Tetromino>(rand() % 7);
		next_block.setBlock(randType);
	}
	else if (isGameState == 1) {
		exit(0);
	}
	isGameState = 0;
}
