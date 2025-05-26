#include <iostream>
#include <cstdlib>
#include <time.h>
#include "GameManager.h"

using namespace std;

GameManager::GameManager():randType(Tetromino::I)
{
	srand((unsigned int)time(NULL));
}

GameManager::~GameManager()
{

}

void GameManager::play()
{
	renderer.drawBoard(board);
	init();
	int i = 0;
	while (true) {
		Sleep(500);
		update();
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
}

void GameManager::update()
{
	if (current_block.getY() + current_block.getShape().size() != Board::height - 1) {
		renderer.eraseBlock(current_block);
		current_block.move(0, 1);
	}
	
	renderer.drawBlock(current_block);
	/*randType = static_cast<Tetromino>(rand() % 7);
	current_block = next_block;
	next_block.setBlock(randType);*/
}
