#include "Block.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Block::Block(const bool& shape) // ���� �Ŵ��� Ŭ������ ��ĥ �� ���� Ȯ�� ���� ������� ����� ����
{
	if (shape)
		block_size = 4; // ���� ���� ���
	else
		block_size = 3; // �̿� ��Ÿ ���� ���
	block = make_unique<unique_ptr<int[]>[]>(block_size); // ����Ʈ �����ͷ� �� ����
	getshape(); // ���� ���� ���߹迭�� �Ҵ��ϰ� ��� ����
}

Block::Block(Block& b1) // ���� ������
	:block_size(b1.block_size) // �Ϲ� �����ڿ����� parameter�� true or false�� ���������� ���⼭�� block_size�� ���� ����
{
	block = make_unique<unique_ptr<int[]>[]>(block_size);
	for (size_t i = 0; i < block_size; i++) {
		block[i] = make_unique<int[]>(block_size);
		for (size_t j = 0; j < block_size; j++) {
			block[i][j] = b1.block[i][j]; // �迭 ���� ����
		}
	}
}

Block::~Block() // ����Ʈ �����ͷ� �ۼ�. delete �ʿ� x
{
}

void Block::getshape()
{
	int ran = 0;
	if (block_size == 3) { //3x3�� �ش��ϴ� ���� ��� ���� �����ؼ� ���� �� �Ҵ�
		srand((unsigned)time(NULL));
		ran = rand() % 6 + 1;
	}
	ifstream fin("blockshape.txt"); // �� ���� ���� �ؽ�Ʈ ����
	if (!fin) {
		cout << "FIle not found"; // ���� �������� ���� �� ���� x
		return;
	}
	int count = 0;
	string str;
	while (count < 5 * ran && !fin.eof()) { // 5�� �������� �ۼ��Ͽ����Ƿ� ������ ����ŭ �� �� ������ �о������(����ģ��)
		getline(fin, str);
		count++;
	}
	for (size_t i = 0; i < block_size && !fin.eof(); i++) { // �츮�� ������ �� ���� �����ϱ�
		block[i] = make_unique<int[]>(block_size); // ���� �迭 �Ҵ�
		getline(fin, str); // ���ڿ� �а�
		stringstream ss(str); // ���ڿ� �и��� �� stringstream
		char ch;
		for (size_t k = 0; ss.get(ch); k++) { // �� ���ھ� �и�
			block[i][k] = ch - '0'; // �ؽ�Ʈ �����̶� ���� �����̹Ƿ� '0'�� ���ش�.
		}
	}
}

void Block::rotate_block() // �ӽ÷� ������ ���� �迭 ������ �� ȸ�� ������ �����Ͽ� ���� �� ������ �̵�
{
	unique_ptr<unique_ptr<int[]>[]> rotateblock = make_unique<unique_ptr<int[]>[]>(block_size); // ���� ����Ʈ ������ �迭 ����
	rotateblock = make_unique<unique_ptr<int[]>[]>(block_size);
	for (size_t i = 0; i < block_size; i++) {
		rotateblock[i] = make_unique<int[]>(block_size);
	}
	for (size_t j = 0; j < block_size; j++) {
		for (size_t k = 0; k < block_size; k++) {
			rotateblock[j][k] = block[block_size - k - 1][j]; // 90�� ȸ��(1�� -> 1��, 2�� -> 2�� ... n��(3 or 4) -> n��)
		}
	}
	block = move(rotateblock); // ���� �̵�
	rotateblock = nullptr; // ���� �����ߴ� ���� ����
}

