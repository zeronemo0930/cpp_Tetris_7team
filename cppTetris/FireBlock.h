#pragma once
#include "Block.h"

class FireBlock :public Block {
public:
	FireBlock() :Block(Tetromino::B) {};
	void specialFunc(Board& board) override;
};
