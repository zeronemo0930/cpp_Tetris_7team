#pragma once
#include "Block.h"
#include "Board.h"

class FireBlock :public Block {
public:
	FireBlock() :Block(Tetromino::B) {};
	void specialFunc(Board& board) override;
};
