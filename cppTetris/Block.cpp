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
	x = 7;
	y = 0;
	type = t;
	switch (t)
	{
	case Tetromino::I:
		shape = {
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0}
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
			{0, 0, 0},
			{1, 1, 1},
			{0, 1, 0}
		};
		break;
	case Tetromino::J:
		shape = {
			{0, 0, 0},
			{1, 1, 1},
			{0, 0, 1}
		};
		break;
	case Tetromino::L:
		shape = {
			{0, 0, 0},
			{1, 1, 1},
			{1, 0, 0}
		};
		break;
	case Tetromino::S:
		shape = {
			{0, 0, 0},
			{0, 1, 1},
			{1, 1, 0}
		};
		break;
	case Tetromino::Z:
		shape = {
			{0, 0, 0},
			{1, 1, 0},
			{0, 1, 1}
		};
		break;
	}
}

void Block::rotate()
{
	if (type == Tetromino::O) return;
	size_t m = shape.size();
	size_t n = shape[0].size();
	shapeVec rotated;
	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			rotated[i][j] = shape[j][m - i];
		}
	}
	shape = rotated;
}

void Block::move(int dx, int dy)
{
	x += dx;
	y += dy;
}
