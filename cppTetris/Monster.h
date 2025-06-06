#pragma once
#include <vector>
#include <string>
// Monster
enum class MonsterName {
    Square, Water, Castle, greenhate
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
    Monster& setMonsterShape(int stage);
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
            "Square: ������ �Ϻ��ؾ� �Ѵ�.",
            "Square: �߶Ծ����� �� ��.",
            "�׸� ���� ������ ���� ���� �� ���� ����� ���."
        },

        // Stage 1: ������ ������
        {
            "����: �� ���... ����� ��� �ٲ��!",
            "����: ��Ģ�� ���� �ش��� ���̱⵵ ����.",
            "�� ���: �� �귯���� ��� ��������. ��ƺ�����?",
            "�� ���: ���´� ������, �ʵ� ������ ���Ұ�.",
            "Ư���� ��� �� ���� �� ����."
        },

        // Stage 2: �߷��� ���� && ȸ�� �� ��� ����
        {
            "����: �� �ӵ�... ��ȭ��?",
            "����: ������ Ǯ�� ����. ������, ����.",
            "����: �ϳ�, ��... ����! �̰��!",
            "ĳ�� ���: ���⼱ �������� �� �й��.",
            "�Ǵ��� ������ �ؾ� �� �� ����."
        },

        // Stage 3: ������ �Ƕ�̵�
        {
            "�׸��÷�: �� �׸��� �� �μŹ����� �;�... �׸���...",
            "�׸��÷�: ȥ���� �Ƹ�����. ������ �� ��������.",
            "�׸��÷�: �� �ϳ��� �� �帧�� ���� �� ������?",
            "����: �׸� �÷�! �ʰ� ���� ȥ���� ������ �ٷ� ��ھ�!",
            "����: �����̾�, ģ����! ������ ���� ������!",
            "�μ��� ��ϵ��� ��Ʈ����â�� �ʷ����� �����δ�."
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
