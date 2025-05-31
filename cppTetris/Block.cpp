#include "Block.h"

Block::Block() : Block(Tetromino::I)
{
}

Block::Block(Tetromino t) :x(7), y(0)
{
	setBlock(t);
}

Block::~Block()
{
}



void Block::setBlock(Tetromino t)
{
	x = 15;
	y = 1;
	type = t;
	switch (t)
	{
	case Tetromino::I:
		shape = {
			{0, 1},
			{0, 1},
			{0, 1},
			{0, 1}
		};
		break;
	case Tetromino::O:
		shape = {
			{1, 1},
			{1, 1}
		};
		break;
	case Tetromino::T:
		shape = {
			{1, 1, 1},
			{0, 1, 0}
		};
		break;
	case Tetromino::J:
		shape = {
			{1, 1, 1},
			{0, 0, 1}
		};
		break;
	case Tetromino::L:
		shape = {
			{1, 1, 1},
			{1, 0, 0}
		};
		break;
	case Tetromino::S:
		shape = {
			{0, 1, 1},
			{1, 1, 0}
		};
		break;
	case Tetromino::Z:
		shape = {
			{1, 1, 0},
			{0, 1, 1}
		};
		break;
	}
}

void Block::rotate()
{
	if (type == Tetromino::O) return;

	size_t n = shape.size();
	size_t m = shape[0].size();
	shapeVec rotated(m, std::vector<int>(n));

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			rotated[j][n - 1 - i] = shape[i][j];
		}
	}

	shape = std::move(rotated);
}


void Block::move(short dx, short dy)
{
	x += dx;
	y += dy;
}

void Block::setPosition(short x, short y)
{
	this->x = x;
	this->y = y;
}
