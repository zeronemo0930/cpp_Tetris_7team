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

    static constexpr const char* SCRIPT[4][5] = {
        // Stage 0: ������ ���
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
            nullptr
        },

        // Stage 2: �߷��� ����
        {
            "����: �� �ӵ�... ��ȭ��?",
            "����: ������ Ǯ�� ����. ������, ����.",
            "����: �ϳ�, ��... ����! �̰��!",
            "�ȳ� ���: ���⼱ �������� �� �й��.",
            nullptr
        },

        // Stage 3: ������ �Ƕ�̵�
        {
            "�׸��÷�: ȥ���� �Ƹ�����. ������ �� ��������.",
            "�׸��÷�: �� �ϳ��� �� �帧�� ���� �� ������?",
            "����: �츰 ���� �ٸ�����... �Բ���� ���� �� �־�!",
            "����: �����̾�, ģ����! ������ ���� ������!",
            nullptr
        }
    };

	

	static const char* const* getScriptLine(int s) {
		return SCRIPT[s];
		return NULL;
	}

private:
	MonsterName current_Monster;
	monsterVec monsterShape;

	int speed;
	int stick_rate;

	int MaxHp;
	int currentHp;
};
