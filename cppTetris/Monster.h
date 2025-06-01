#pragma once
#include <vector>
#include <string>
// Monster �̸�, ���̵� �ٽ� ���ϱ�
enum class MonsterName {
	RAT, GHOST, HAMSTER
};

using monsterVec = std::vector<std::string>;

class Monster
{
public:
	Monster() = delete;
	Monster(MonsterName name);
	~Monster();

	void takeDamage() { currentHp--; }
	bool isDead() const { return currentHp <= 0; }
	monsterVec& getMonsterVec() { return this->monsterShape; }
	int getMaxHp() { return this->MaxHp; }
	int getCurrentHp() { return this->currentHp; }
private:
	MonsterName current_Monster;
	monsterVec monsterShape;

	static int stage;
	int speed;
	int stick_rate;

	int MaxHp;
	int currentHp;
};
