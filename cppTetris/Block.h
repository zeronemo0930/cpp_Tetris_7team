/*
* 블럭 초기 위치 : (15, 1), 게임 화면 상 next_block이 표시되는 위치.
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

	// int대신 short을 사용할까?
	short x, y;
};

