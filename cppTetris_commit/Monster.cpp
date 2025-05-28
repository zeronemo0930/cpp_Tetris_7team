#include "Monster.h"

Monster::Monster(MonsterName name) : current_Monster(name){
	
	switch (name)
	{
	case MonsterName::MONSTER1:
		speed = 40;
		stick_rate = 20;
		hp = 10;
		break;
	case MonsterName::MONSTER2:
		speed = 40;
		stick_rate = 20;
		hp = 10;
		break;
	case MonsterName::MONSTER3:
		speed = 40;
		stick_rate = 20;
		hp = 10;
		break;
	}
}

Monster::~Monster()
{
}
