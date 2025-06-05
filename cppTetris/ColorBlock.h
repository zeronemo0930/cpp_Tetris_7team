#pragma once
#include "Block.h"
#include "Renderer.h"
class ColorBlock :public Block {
public:
	ColorBlock() :Block(Tetromino::B) {};
	void specialFunc(Board& board) override;
private:
	int colNum = 0;
}

