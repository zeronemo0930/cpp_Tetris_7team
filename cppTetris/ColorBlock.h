#pragma once
#include "Block.h"

class ColorBlock :public Block {
public:
	ColorBlock() :Block(Tetromino::B) {};
	void specialFunc(Board& board) override;
private:
	int colNum = 0;
}

