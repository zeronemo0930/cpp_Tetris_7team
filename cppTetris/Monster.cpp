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

Monster& Monster::setMonsterShape(int stage) {
    switch (stage) {
    case 0:
        current_Monster = MonsterName::Square;
        break;
    case 1:
        current_Monster = MonsterName::Water;
        break;
    case 2:
        current_Monster = MonsterName::Castle;
        break;
    case 3:
        current_Monster = MonsterName::greenhate;
        break;

    }
    SetMonster(current_Monster);
    return *this;
}

void Monster::SetMonster(MonsterName name) // 임시 보스 설정
{
    switch (name)
    {
    case MonsterName::Square:
        speed = 40;
        stick_rate = 20;
        MaxHp = 1;
        monsterShape = 
            {
    " +--------+ ",
    " |        | ",
    " |  [][]  | ",
    " |        | ",
    " +--------+ "


        };

        break;
    case MonsterName::Water:
        speed = 20;
        stick_rate = 15;
        MaxHp = 2;
        monsterShape.clear();
        monsterShape = {
    "   ~~~~~~~~   ",
    "  /        \\  ",
    " |   ~~~    | ",
    "  \\        /  ",
    "   ~~~~~~~~   "
        };

        break;
    case MonsterName::Castle:
        speed = 4;
        stick_rate = 10;
        MaxHp = 3;
        monsterShape.clear();
        monsterShape = {
    " |^^^^^^^| ",
    " |  |||  | ",
    " |  |||  | ",
    " |__|||__| ",
    " |_______| "
        } ;


        break;
    case MonsterName::greenhate:
        speed = 4;
        stick_rate = 10;
        MaxHp = 10;
        monsterShape.clear();
        monsterShape = {
    "   /~~~~~~~\\  ",
    "  |  >_<   | ",
    "  | [] []  | ",
    "  |   ^    | ",
    "   \\_____ /  "
        };


        break;
    }
    currentHp = MaxHp;
}




