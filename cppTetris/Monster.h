#pragma once
#include <vector>
#include <string>
// Monster
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


    std::vector<std::vector<std::string>> SCRIPTS = {
           {
            "����: ...���Ⱑ �����...?",
            "����: ����� ��Ʈ���� ������ �� ����.",
            "����: �켱 �տ� ���̴� �׸� ��Ϻ��� ó������.",
            "Squarebot: ������ �Ϻ��ؾ� �Ѵ�.",
            "Squarebot: �߶Ծ����� �� ��."
        },

        // Stage 1: ������ ������
        {
            "����: �� ���... ����� ��� �ٲ��!",
            "����: ��Ģ�� ���� �ش��� ���̱⵵ ����.",
            "�� ���: �� �귯���� ��� ��������. ��ƺ�����?",
            "�� ���: ���´� ������, �ʵ� ������ ���Ұ�.",

        },

        // Stage 2: �߷��� ����
        {
            "����: �� �ӵ�... ��ȭ��?",
            "����: ������ Ǯ�� ����. ������, ����.",
            "����: �ϳ�, ��... ����! �̰��!",
            "�ȳ� ���: ���⼱ �������� �� �й��.",
        },

        // Stage 3: ������ �Ƕ�̵�
        {
            "�׸��÷�: ȥ���� �Ƹ�����. ������ �� ��������.",
            "�׸��÷�: �� �ϳ��� �� �帧�� ���� �� ������?",
            "����: �츰 ���� �ٸ�����... �Բ���� ���� �� �־�!",
            "����: �����̾�, ģ����! ������ ���� ������!",
        }

    };
    std::vector<std::string> getScriptLine(int s) {
   
            return SCRIPTS[s];
        
    }


private:
	MonsterName current_Monster;
	monsterVec monsterShape;

	int speed;
	int stick_rate;

	int MaxHp;
	int currentHp;
};
