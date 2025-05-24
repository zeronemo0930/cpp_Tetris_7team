#include "Block.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Block::Block(const bool& shape) // 게임 매니저 클래스와 합칠 때 막대 확률 변수 기반으로 계산할 예정
{
	if (shape)
		block_size = 4; // 막대 블럭의 경우
	else
		block_size = 3; // 이외 기타 블럭의 경우
	block = make_unique<unique_ptr<int[]>[]>(block_size); // 스마트 포인터로 블럭 생성
	getshape(); // 블럭의 동적 이중배열을 할당하고 모양 결정
}

Block::Block(Block& b1) // 복사 생성자
	:block_size(b1.block_size) // 일반 생성자에서는 parameter의 true or false로 진행했으나 여기서는 block_size를 사전 정의
{
	block = make_unique<unique_ptr<int[]>[]>(block_size);
	for (size_t i = 0; i < block_size; i++) {
		block[i] = make_unique<int[]>(block_size);
		for (size_t j = 0; j < block_size; j++) {
			block[i][j] = b1.block[i][j]; // 배열 정보 복사
		}
	}
}

Block::~Block() // 스마트 포인터로 작성. delete 필요 x
{
}

void Block::getshape()
{
	int ran = 0;
	if (block_size == 3) { //3x3에 해당하는 블럭일 경우 난수 지정해서 랜덤 블럭 할당
		srand((unsigned)time(NULL));
		ran = rand() % 6 + 1;
	}
	ifstream fin("blockshape.txt"); // 블럭 정보 저장 텍스트 파일
	if (!fin) {
		cout << "FIle not found"; // 파일 존재하지 않을 때 실행 x
		return;
	}
	int count = 0;
	string str;
	while (count < 5 * ran && !fin.eof()) { // 5줄 간격으로 작성하였으므로 난수의 값만큼 각 블럭 모형을 읽어내려간다(지나친다)
		getline(fin, str);
		count++;
	}
	for (size_t i = 0; i < block_size && !fin.eof(); i++) { // 우리가 지정할 블럭 정보 저장하기
		block[i] = make_unique<int[]>(block_size); // 이중 배열 할당
		getline(fin, str); // 문자열 읽고
		stringstream ss(str); // 문자열 분리해 줄 stringstream
		char ch;
		for (size_t k = 0; ss.get(ch); k++) { // 한 글자씩 분리
			block[i][k] = ch - '0'; // 텍스트 파일이라 문자 형태이므로 '0'을 빼준다.
		}
	}
}

void Block::rotate_block() // 임시로 정수형 이중 배열 생성한 후 회전 정보를 저장하여 기존 블럭 정보에 이동
{
	unique_ptr<unique_ptr<int[]>[]> rotateblock = make_unique<unique_ptr<int[]>[]>(block_size); // 이중 스마트 포인터 배열 생성
	rotateblock = make_unique<unique_ptr<int[]>[]>(block_size);
	for (size_t i = 0; i < block_size; i++) {
		rotateblock[i] = make_unique<int[]>(block_size);
	}
	for (size_t j = 0; j < block_size; j++) {
		for (size_t k = 0; k < block_size; k++) {
			rotateblock[j][k] = block[block_size - k - 1][j]; // 90도 회전(1행 -> 1열, 2행 -> 2열 ... n행(3 or 4) -> n열)
		}
	}
	block = move(rotateblock); // 정보 이동
	rotateblock = nullptr; // 기존 저장했던 변수 비우기
}

