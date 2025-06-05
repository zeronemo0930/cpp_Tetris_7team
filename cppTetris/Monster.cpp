#include "Monster.h"
#include <iostream>

using namespace std;

int Monster::stage = 0;

Monster::Monster(MonsterName name) : current_Monster(name){
	SetMonster(name);
}

Monster::~Monster()
{
}

Monster& Monster::getNextMonster() {

	switch (current_Monster) {
	case MonsterName::RAT:
		current_Monster = MonsterName::GHOST;
		break;
	case MonsterName::GHOST:
		current_Monster = MonsterName::CAT;
		break;
	case MonsterName::CAT:
		break;
	}
	SetMonster(current_Monster);
	return *this;
}

void Monster::SetMonster(MonsterName name) // 임시 보스 설정
{
	switch (name)
	{
	case MonsterName::RAT:
		speed = 40;
		stick_rate = 20;
		MaxHp = 1;
		monsterShape = {
			"`;-.          ___,",
			"  `.`\\_...._/`.-\"`",
			"    \\        /      ,",
			"    /()   () \\    .' `-._",
			"   |)  .    ()\\  /   _.'",
			"   \\  -'-     ,; '. <",
			"    ;.__     ,;|   > \\",
			"   / ,    / ,  |.-'.-'",
			"  (_/    (_/ ,;|.<`",
			"    \\    ,     ;-`",
			"     >   \\    /",
			"    (_,-'`> .'",
			"          (_,'"
		};
		break;
	case MonsterName::GHOST:
		speed = 20;
		stick_rate = 15;
		MaxHp = 1;
		monsterShape.clear();
		monsterShape = {
			"     .-'      `-.",
			"    /            \\",
			"   |              |",
			"   |,  .-.  .-.  ,|",
			"   | )(_o/  \\o_)( |",
			"   |/     /\\     \\|",
			"   (_     ^^     _)",
			"    \\__|IIIIII|__/",
			"     | \\IIIIII/ |",
			"     \\          /",
			"      `--------`"
		};
		break;
	case MonsterName::CAT:
		speed = 4;
		stick_rate = 10;
		MaxHp = 10;
		monsterShape.clear();
		monsterShape = {
			" /\\     /\\",
			"{  `---'  }",
			"{  O   O  }",
			"~~>  V  <~~",
			" \\  \\|/  /",
			"  `-----'____",
			" /     \\    \\_",
			"{       }\\  )_\\_   _",
			"|  \\_/  |/ /  \\_\\_/ )",
			" \\__/  /(_/     \\__/",
			"   (__/"
		};
		break;
	}
	currentHp = MaxHp;
}



