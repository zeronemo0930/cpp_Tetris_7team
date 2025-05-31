/*
* �� �ʱ� ��ġ : (15, 1), ���� ȭ�� �� next_block�� ǥ�õǴ� ��ġ.
*/

#pragma once
#include <vector>

enum class Tetromino{ I, O, T, J, L, S, Z};
using shapeVec = std::vector<std::vector<int>>;
class Block
{
public:
	Block();
	Block(Tetromino t);
	~Block();

	void setBlock(Tetromino t);
	void rotate();
	void move(short dx, short dy);
	void setPosition(short x, short y);
	const shapeVec& getShape() const { return shape; };

	int getX() const { return x; };
	int getY() const { return y; };
	Tetromino getType() { return type; };
	
private:
	shapeVec shape;
	Tetromino type;

	// int��� short�� ����ұ�?
	short x, y;
};

