#include "Block.h"
#include "Board.h"

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


// Vector를 이용해서 배열 크기를 블럭 사이즈에 딱 맞게 수정하면, 회전의 조작감이 구려짐
void Block::setBlock(Tetromino t)
{
	x = 17;
	y = 1;
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
			{2, 2},
			{2, 2}
		};
		break;
	case Tetromino::T:
		shape = {
			{0, 0, 0},
			{3, 3, 3},
			{0, 3, 0}
		};
		break;
	case Tetromino::J:
		shape = {
			{0, 0, 0},
			{4, 4, 4},
			{0, 0, 4}
		};
		break;
	case Tetromino::L:
		shape = {
			{0, 0, 0},
			{5, 5, 5},
			{5, 0, 0}
		};
		break;
	case Tetromino::S:
		shape = {
			{0, 0, 0},
			{0, 6, 6},
			{6, 6, 0}
		};
		break;
	case Tetromino::Z:
		shape = {
			{0, 0, 0},
			{7, 7, 0},
			{0, 7, 7}
		};
		break;

	case Tetromino::B:
		shape = {
			{8}
		};
		break;
	}
}

void Block::rotate()
{
	if (type == Tetromino::O) return;

	size_t n = shape.size(); // 정방행렬이므로 행 == 열
	shapeVec rotated(n, std::vector<int>(n));

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			rotated[i][j] = shape[n - 1 - j][i];
		}
	}

	shape = rotated;
}


void Block::move(short dx, short dy)
{
	x += dx;
	y += dy;
}

void Block::setPos(short x, short y)
{
	this->x = x;
	this->y = y;
}

void Block::specialFunc(Board& board)
{
}
