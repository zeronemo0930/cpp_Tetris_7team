#pragma once
#include "Block.h"

class WaterBlock :public Block{
public:
	WaterBlock() : Block(Tetromino::B) {};
	void specialFunc(Board& board) override;
};
