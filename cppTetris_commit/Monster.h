#pragma once


// Monster 이름, 난이도 다시 정하기
enum class MonsterName {
	MONSTER1, MONSTER2, MONSTER3
};

class Monster
{
public:
	Monster() = delete;
	Monster(MonsterName name);
	~Monster();

private:
	MonsterName current_Monster;

	int speed;
	int stick_rate;
	int hp;
};
