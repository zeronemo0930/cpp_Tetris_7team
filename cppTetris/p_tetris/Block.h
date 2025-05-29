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
	void move(int dx, int dy);
	const shapeVec& getShape() const { return shape; };

	int getX() { return x; };
	int getY() { return y; };
	Tetromino getType() { return type; };
	
private:
	shapeVec shape;
	Tetromino type;

	int x, y;
};