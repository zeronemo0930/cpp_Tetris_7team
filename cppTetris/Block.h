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
	friend ostream& operator<< (ostream& out, Block b); //  확인 작업을 위한 overriding, 추후 작업에 쓰일 수 있으니 남겼습니다
public:
	Block() = delete; // 막대 결정하는 parameter 없으면 생성 불가
	Block(const bool& shape); //parameter 통해 막대 블럭인지 아닌지 구분. 블럭 배열 크기 할당 위함.
	Block(Block& b1); // 복사 생성자
	~Block();
	void getshape(); // 기본 생성자 이후 파일에서 막대 모양 참조해서 블럭 객체의 모양 결정
	void rotate_block(); // 기존 블럭을 90℃ 회전한 도형을 기존 block에 갱신
};



