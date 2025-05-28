#pragma once


// Monster �̸�, ���̵� �ٽ� ���ϱ�
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
