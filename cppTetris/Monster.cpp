#include "Monster.h"
#include "Monster.h"
#include <iostream>

using namespace std;

int Monster::stage = 0;

Monster::Monster(MonsterName name) : current_Monster(name){
	
	switch (name)
	{
	case MonsterName::SLIME:
		speed = 40;
		stick_rate = 20;
		hp = 10;
		break;
	case MonsterName::GHOST:
		speed = 20;
		stick_rate = 15;
		hp = 12;
		break;
	case MonsterName::HAMSTER:
		speed = 4;
		stick_rate = 10;
		hp = 1000;
		break;
	}
}

Monster::~Monster()
{
}

void Monster::printMonster() const
{	
	switch (current_Monster) {
	case MonsterName::SLIME:
		cout << R"(
     _____
   /       \
  |  o   o  |
  |   ~~~   |
   \_______/
)" << endl;
		break;

	case MonsterName::GHOST:
		cout << R"(
     .-"      "-.
   /    O  O     \
  |      ■■■      |	
  \   \_____/    /
   "-.________.-"
     /  |  |  \
    /   |  |   \
)" << endl;
		break;

	case MonsterName::HAMSTER:
		cout << R"(
    (\__/)
  ( oㅅo )
  / 　 づ♡
 /|     |\
(_|     |_)
)" << endl;
		break;
	}

}

void Monster::printStatus() const {
	cout << "========== Monster Info ==========\n";
	switch (current_Monster) {
	case MonsterName::SLIME:
		cout << "Name       : Slime\n";
		break;
	case MonsterName::GHOST:
		cout << "Name       : Ghost\n";
		break;
	case MonsterName::HAMSTER:
		cout << "Name       : Hamster\n";
		break;
	}
	cout << "HP         : " << hp << "\n";
	cout << "==================================\n";
}

Monster* Monster::getNextMonster()		//monster 생성할 때 사용, 레벨 바뀔때 delete후 다시 사용
{
	if (stage == 0) {
		stage++;
		return new Monster(MonsterName::SLIME);
	}
	else if (stage == 1) {
		stage++;
		return new Monster(MonsterName::GHOST);
	}
	else if (stage == 2) {
		stage++;
		return new Monster(MonsterName::HAMSTER);
	}
	else {
		return nullptr;
	}
}
