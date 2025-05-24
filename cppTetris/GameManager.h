#pragma once
#include <iostream>
#include "Renderer.h"
#include "Board.h"

using namespace std;

class GameManager
{
private:
	Board board;


	Renderer renderer;
	
public:
	GameManager();
	~GameManager();

	void play();

	void init();
	void input();
	void update();
};

