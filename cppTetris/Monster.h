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
        // Stage 0: 시작의 블록
        {
            "조아: ...여기가 어디지...?",
            "조아: 여기는 테트리스 세계인 거 같다.",
            "조아: 우선 앞에 보이는 네모 블록부터 처리하자.",
            "Squarebot: 각도는 완벽해야 한다.",
            "Squarebot: 삐뚤어지면 안 돼."
        },

        // Stage 1: 엇갈린 조각들
        {
            "조아: 이 블록... 모양이 계속 바뀌어!",
            "조아: 규칙을 깨면 해답이 보이기도 하지.",
            "물 블록: 난 흘러가는 대로 움직이지. 잡아보시지?",
            "물 블록: 형태는 없지만, 너도 마시진 못할걸.",
            nullptr
        },

        // Stage 2: 중력의 시험
        {
            "조아: 이 속도... 실화야?",
            "조아: 긴장을 풀면 진다. 집중해, 조아.",
            "조아: 하나, 둘... 스핀! 이겼다!",
            "안내 블록: 여기선 망설임이 곧 패배다.",
            nullptr
        },

        // Stage 3: 결전의 피라미드
        {
            "그린시러: 혼돈은 아름답지. 예측할 수 없을수록.",
            "그린시러: 너 하나로 이 흐름을 막을 수 있을까?",
            "조아: 우린 각자 다르지만... 함께라면 맞출 수 있어!",
            "조아: 지금이야, 친구들! 마지막 줄을 맞춰줘!",
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
