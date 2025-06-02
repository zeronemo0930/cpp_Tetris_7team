#include "Monster.h"
#include "Monster.h"
#include <iostream>

using namespace std;

int Monster::stage = 0;

Monster::Monster(MonsterName name) : current_Monster(name){
	//
	switch (name)
	{
	case MonsterName::RAT:
		speed = 40;
		stick_rate = 20;
		MaxHp = 10;
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
		MaxHp = 12;
		break;
	case MonsterName::HAMSTER:
		speed = 4;
		stick_rate = 10;
		MaxHp = 1000;
		break;
	}
	currentHp = MaxHp;
}

Monster::~Monster()
{
}

