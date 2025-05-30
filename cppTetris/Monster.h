#pragma once


// Monster 이름, 난이도 다시 정하기
enum class MonsterName {
	SLIME, GHOST, HAMSTER
};

class Monster
{
public:
	Monster() = delete;
	Monster(MonsterName name);
	~Monster();
	void printMonster() const;
	void printStatus() const;
	void takeDamage() { hp--; }
	bool isDead() const { return hp <= 0; }
	static Monster* getNextMonster();

private:
	MonsterName current_Monster;
	static int stage;
	int speed;
	int stick_rate;
	int hp;
};
