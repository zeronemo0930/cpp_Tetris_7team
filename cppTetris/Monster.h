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
            "조아: ...여기가 어디지...?",
            "조아: 여기는 테트리스 세계인 거 같다.",
            "조아: 우선 앞에 보이는 네모 블록부터 처리하자.",
            "Square: 각도는 완벽해야 한다.",
            "Square: 삐뚤어지면 안 돼.",
            "네모 블럭이 굉장히 자주 나올 것 같은 기분이 든다."
        },

        // Stage 1: 엇갈린 조각들
        {
            "조아: 이 블록... 모양이 계속 바뀌어!",
            "조아: 규칙을 깨면 해답이 보이기도 하지.",
            "물 블록: 난 흘러가는 대로 움직이지. 잡아보시지?",
            "물 블록: 형태는 없지만, 너도 마시진 못할걸.",
            "특이한 블록 이 나올 것 같다."
        },

        // Stage 2: 중력의 시험 && 회전 시 블록 렌덤
        {
            "조아: 이 속도... 실화야?",
            "조아: 긴장을 풀면 진다. 집중해, 조아.",
            "조아: 하나, 둘... 스핀! 이겼다!",
            "캐슬 블록: 여기선 망설임이 곧 패배다.",
            "판단을 빠르게 해야 할 것 같다."
        },

        // Stage 3: 결전의 피라미드
        {
            "그린시러: 난 그린은 다 부셔버리고 싶어... 그리고...",
            "그린시러: 혼돈은 아름답지. 예측할 수 없을수록.",
            "그린시러: 너 하나로 이 흐름을 막을 수 있을까?",
            "조아: 그린 시러! 너가 만든 혼돈의 세상을 바로 잡겠어!",
            "조아: 지금이야, 친구들! 마지막 줄을 맞춰줘!",
            "부셔진 블록들이 테트리스창을 초록으로 물들인다."
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
