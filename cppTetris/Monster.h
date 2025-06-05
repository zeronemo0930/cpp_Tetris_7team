#pragma once
#include <vector>
#include <string>
// Monster ÀÌ¸§, ³­ÀÌµµ ´Ù½Ã Á¤ÇÏ±â
enum class MonsterName {
	RAT, GHOST, CAT
};

using monsterVec = std::vector<std::string>;

class Monster
{
public:
	Monster() = delete;
	Monster(MonsterName name);
	~Monster();

	void takeDamage(int damage) { currentHp -= damage; }
	bool isDead() const { return currentHp <= 0; }
	Monster& getNextMonster();
	void SetMonster(MonsterName name);

	monsterVec& getMonsterVec() { return this->monsterShape; }
	int getMaxHp() { return this->MaxHp; }
	int getCurrentHp() { return (this->currentHp > 0) ? this->currentHp : 0; }
	MonsterName getMonster() {
		return this->current_Monster;
	}
	int getStage() { return stage; }
	static int stage;

	static constexpr const char* SCRIPT[3][5] = {
		{ "player: i win!", "??? : wait.", "player: who!", nullptr, nullptr },
		{ "p!", "BOSS2: 실력이군.", "플: 각오해!", "BOSS2: 덤벼!", nullptr },
		{ "플: 마지막이다!", "BOSS3: 네가 과연?", nullptr, nullptr, nullptr }
	};

	

	static const char* const* getScriptLine(int s) {
		return SCRIPT[s]; // 특정 행 반환
	}

private:
	MonsterName current_Monster;
	monsterVec monsterShape;

	int speed;
	int stick_rate;

	int MaxHp;
	int currentHp;
};
