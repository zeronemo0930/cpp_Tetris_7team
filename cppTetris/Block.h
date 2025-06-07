#pragma once
#include <vector>

class Board;

enum class Tetromino { I, O, T, J, L, S, Z, B };
using shapeVec = std::vector<std::vector<int>>;
class Block
{
public:
	Block();
	Block(Tetromino t);
	virtual ~Block();

	void setBlock(Tetromino t, int stage);
	void rotate();
	void setGreenhateBlock(Tetromino t, int stage);
	void move(short dx, short dy);
	void setPos(short x, short y);
	int getPosX();
	int getPosY();
	const shapeVec& getShape() const { return shape; };
	virtual void specialFunc(Board& board);

	

	int getX() const { return x; };
	int getY() const { return y; };
	Tetromino getType() { return type; };
	
	static inline int limit = 0; // ������ ������ ���� �� �����ϴ� key

private:
	shapeVec shape;
	Tetromino type;
	// int��� short�� ����ұ�?
	short x, y;
};

