#pragma once
#include <iostream>
#include <memory>

using std::ostream;
using std::unique_ptr;

class Block
{
private:
	int block_size;
	unique_ptr<unique_ptr<int[]>[]> block;
	friend ostream& operator<< (ostream& out, Block b); //  Ȯ�� �۾��� ���� overriding, ���� �۾��� ���� �� ������ ������ϴ�
public:
	Block() = delete; // ���� �����ϴ� parameter ������ ���� �Ұ�
	Block(const bool& shape); //parameter ���� ���� ������ �ƴ��� ����. �� �迭 ũ�� �Ҵ� ����.
	Block(Block& b1); // ���� ������
	~Block();
	void getshape(); // �⺻ ������ ���� ���Ͽ��� ���� ��� �����ؼ� �� ��ü�� ��� ����
	void rotate_block(); // ���� ���� 90�� ȸ���� ������ ���� block�� ����
};



