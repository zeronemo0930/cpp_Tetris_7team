#include <iostream>
#include <cstdlib>
#include <time.h>
#include "GameManager.h"
#include <conio.h>
#include "Renderer.h"

#define EXT_KEY			0xffffffe0
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

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
	renderer.show_logo();
	renderer.input_data();
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


void GameManager::update()
{
	renderer.eraseBlock(current_block);
	if (current_block.getY() + current_block.getShape().size() != Board::height - 1)
		current_block.move(0, 1);
	renderer.drawBlock(current_block);

	/*randType = static_cast<Tetromino>(rand() % 7);
	current_block = next_block;
	next_block.setBlock(randType);*/
}

void GameManager::make_new_block()
{


}

void GameManager::processInput()
{
	for (i = 1; 1; i++)
	{
		if (_kbhit())
		{
			keytemp = _getche();
			if (keytemp == EXT_KEY)
			{
				keytemp = _getche();
				switch (keytemp)
				{
				case KEY_UP:

					if (!board.strike_check(current_block))
					{
						renderer.eraseBlock(current_block);
						current_block.rotate();
						renderer.drawBlock(current_block);
					}
					break;
				case KEY_LEFT:	
					if (current_block.getX() > 1)
					{
						renderer.eraseBlock(current_block);
							current_block.setX(-1);
						if (board.strike_check(current_block))
							current_block.setX(1);
						renderer.drawBlock(current_block);
					}
					break;
				case KEY_RIGHT:

					if (current_block.getX() < 14)
					{
						renderer.eraseBlock(current_block);
						current_block.setX(1);
						if (board.strike_check(current_block))
							current_block.setX(-1);
						renderer.drawBlock(current_block);
					}
					break;
				case KEY_DOWN:
					renderer.eraseBlock(current_block);
					isGameover = move_block(current_block);
					renderer.drawBlock(current_block);
					break;
				}
			}
			if (keytemp == 32)
			{
				while (isGameover == 0)
				{
					renderer.eraseBlock(current_block);
					isGameover = move_block(current_block);
				}
				renderer.drawBlock(current_block);
				renderer.show_nextBlock(next_block);
			}
		}
		if (i % monster[level].getSpeed() == 0)
		{
			isGameover = move_block(current_block);
			renderer.drawBlock(current_block);
		}

		if (monster[level].getClearLine() == lines)
		{
			level++;
			lines = 0;
		}
		if (isGameover == 1)
		{
			renderer.show_gameover();
			renderer.SetColor(GRAY);
			break;
		}

		gotoxy(77, 23);
		Sleep(15);
		gotoxy(77, 23);
	}
	if (current_block.getY() + current_block.getShape().size() != Board::height - 1) {
		renderer.eraseBlock(current_block);
		current_block.move(0, 1);
	}
	
	renderer.drawBlock(current_block);
	/*randType = static_cast<Tetromino>(rand() % 7);
	current_block = next_block;
	next_block.setBlock(randType);*/
}
