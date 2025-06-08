#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include <time.h>
#include "GameManager.h"

#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

using namespace std;

GameManager::GameManager():randType(Tetromino::I), keytemp(NULL), isGameState(0), monster(MonsterName::Square), isHold(false), isNowHold(false)
{
	sm.SetMasterVolume(20);
	menu.setPer(&renderer, &sm);
	srand((unsigned int)time(NULL));
}

GameManager::~GameManager()
{

}

void GameManager::start()
{
	while (true) {
		mainMenu();
	}
	
}

void GameManager::mainMenu()
{
	int menuSelector = menu.menu();
	if (menuSelector == 0) {		// Start
		stage();
	}
	else if (menuSelector == 1) {	// Option
		menu.option();
	}
	else if (menuSelector == 2) {	// Exit
		exit(0);
	}
}

// Monster 클래스의 stage 멤버로 스테이지 설정
void GameManager::stage()
{
	int stageSelector = menu.stageSelect();
	monster.stage = -1;
	switch (stageSelector)
	{
	case 0:		// Story 모드 (프롤로그부터 실행)
		play();
		break;
	case 1:		// 1 Stage 프롤로그 대화 스킵하고 게임만
		monster.stage = 0;
		play();
		monster.setMonsterShape(0);
		break;
	case 2:		// 2 Stage 
		monster.stage = 1;
		current_block.limit = 1; // 초기에 eky설정
		monster.setMonsterShape(1);
		play();
		break;
	case 3:		// 3 Stage
		monster.stage = 2;
		current_block.limit = 2;
		monster.setMonsterShape(2);
		play();
		break;
	case 4:		// Boss
		monster.stage = 3;
		current_block.limit = 3;
		monster.setMonsterShape(3);
		play();
		break;
	case 5:		// 무한모드
		monster.stage = 5;
		current_block.limit = 3;
		play();
		break;
	case 6:		// back
		return;
	}
}

void GameManager::play()
{	
	// retry를 선택한다면 다시 여기부터.
	while (true) {	
		// Story모드로 실행 했을 때
		if (monster.stage == -1) {
			vector<string> prolog = { "<프롤로그>",
				" 이 이야기는 그린시러와 그린조아의 다툼으로 벌어집니다.",
				" 테트로니아는 블록들로 이루어진 세계로, 평소엔 조화롭게 돌아가지만,",
				"그린시러의 영향으로 특정 블록들이 자의식을 얻어 제멋대로 움직이며 세계의 균형을 위협하기 시작합니","다.",
				"  이 블록들을 통제할 수 있는 유일한 사람은 전설의 \"테트리스 마스터\"뿐!" };
			renderer.printLineProlog(1, 10, prolog);
			system("cls");
			monster.stage = 0;
			monster.setMonsterShape(0);
		}

		// 무한모드가 아니라면
		if (monster.stage != 5) {
			renderer.drawMonsterTalk(monster);

			vector<string> lines = monster.getScriptLine(monster.stage);
			renderer.printLineAt(1, 15, lines);
			system("cls");

			renderer.drawMonster(monster);
			renderer.drawMonsterHp(monster);
		}
		else {	// 무한모드일때 score 그리기
			renderer.show_game_stat(score);
		}

		init();	// 게임 시작 전 초기화 구문
		int i = 0;
		while (true) {
			while (_kbhit()) _getch();
			while (checkState()) {
				input();
				if (i % (30 - 12 * menu.getDifficulty()) == 0) {
					update();
				}
				i++;
				Sleep(15);
				gotoxy(77, 23);
			}
			if (monster.stage == 4) {
				system("cls");
				monster.stage = -1;
				return;
			}

			int select = menu.retrySelect();
			if (select == 0) {	// retry는 처음 부터 반복
				system("cls");
				break;
			}
			else {				// 메뉴로
				return;
			}
		}
	}
}



void GameManager::init()
{
	// 게임에 필요한 멤버 초기화
	score = 0;
	combo = 0;
	comboTimer = 0;

	// 게임 틀 렌더
	board.resetBoard();			// 보드 초기화
	renderer.drawBoard(board);
	renderer.nextBlockFrame();
	renderer.holdBlockFrame();
	isHold = false;
	isGameState = 0;

	if (monster.stage >= 0 && monster.stage <= 3) {														// 몬스터가 안그려져요..
		monster.setMonsterShape(monster.stage);
		renderer.drawMonster(monster);
	}

	randType = static_cast<Tetromino>(rand() % 8);
	if (monster.stage == 0 && rand() % 3 == 0) randType = static_cast<Tetromino>(1);                            // 네모만 나오게 함
	else if (monster.stage == 0) randType = static_cast<Tetromino>(rand() % 7);
	if (monster.stage == 3) current_block.setGreenhateBlock(randType, monster.stage);
	else current_block.setBlock(randType, monster.stage);

	current_block.setPos(5, 0);
	randType = static_cast<Tetromino>(rand() % 8);
	if (monster.stage == 0 && rand() % 3 == 0) randType = static_cast<Tetromino>(1);                            // 네모만 나오게 함
	else if (monster.stage == 0) randType = static_cast<Tetromino>(rand() % 7);
	if (monster.stage == 3) next_block.setGreenhateBlock(randType, monster.stage);
	else next_block.setBlock(randType, monster.stage);
	renderer.drawBlock(next_block, false);
	shadowBlock(true);
}

void GameManager::input()
{
	
	if (_kbhit()) {
		keytemp = _getch();
		if (keytemp == EXT_KEY) {
			keytemp = _getch();

			switch (keytemp) 
			{
			case KEY_UP:	// 회전
				moveRotate();
				break;

			case KEY_LEFT:	// 왼쪽으로 이동
				moveLeft();
				break;

			case KEY_RIGHT:	// 오른쪽으로 이동
				moveRight();
				break;

			case KEY_DOWN:	// 아래로 이동
				moveDown();
				break;
			}
		}
		if (keytemp == 32)	//스페이스바를 눌렀을때
		{
			moveSpace();
		}
		// HOLD 시키는 거
		else if (keytemp == 99 || keytemp == 67) {	// c, C를 입력 했을 때
			hold();
		}
	}
}

void GameManager::update()
{
	renderer.eraseBlock(current_block);
	isGameState = board.move_block(current_block);

	renderer.drawBlock(current_block, false);
	checkState();

	if (monster.stage == 5) {
		if (comboTimer > 0) {								// 콤보 타이머 감소
			comboTimer--;
			if (comboTimer == 0) {
				combo = 0;
				gotoxy(43, 13);
				cout << "COMBO: 0   "; // 콤보 리셋 출력
			}
		}
	}
}

void GameManager::moveRotate()
{
	renderer.eraseBlock(current_block);
	if(board.rotate_shift(current_block)) // rotate할 때 strike_check 여부를 확인하고 rotate 가능한 좌표로 변환해주는 rotate_shift
		sm.playEffect("SoundEffects/block_rotate.wav");
	shadowBlock(false);
	renderer.drawBlock(current_block, false);
}

void GameManager::moveLeft()
{
	renderer.eraseBlock(current_block);
	current_block.move(-1, 0);
	if (board.strike_check(current_block))
		current_block.move(1, 0);
	shadowBlock(false);
	renderer.drawBlock(current_block, false);
	sm.playEffect("SoundEffects/block_move.wav");
}

void GameManager::moveRight()
{
	if (current_block.getX() >= Board::width - 1) return;
	renderer.eraseBlock(current_block);
	current_block.move(1, 0);
	if (board.strike_check(current_block))
		current_block.move(-1, 0);
	shadowBlock(false);
	renderer.drawBlock(current_block, false);
	sm.playEffect("SoundEffects/block_move.wav");
}

void GameManager::moveDown()
{
	renderer.eraseBlock(current_block);
	isGameState = board.move_block(current_block);
	renderer.drawBlock(current_block, false);
	sm.playEffect("SoundEffects/block_move.wav");
}

void GameManager::moveSpace()
{
	renderer.eraseBlock(current_block);
	while (isGameState == 0) {
		isGameState = board.move_block(current_block);
	}
	sm.playEffect("SoundEffects/gravity.wav");

}

void GameManager::hold()
{
	if (isNowHold) return;
	if (!isHold) {
		hold_block = current_block;
		makeNewBlock();
		isHold = true;
		
	}
	else{
		renderer.eraseBlock(hold_block);
		renderer.eraseBlock(current_block);
		Block temp_block;
		temp_block = current_block;
		current_block = hold_block;
		hold_block = temp_block;
		current_block.setPos(5, 0);



		renderer.drawBlock(current_block, false);
		shadowBlock(false);
	}
	hold_block.setPos(-6, 1);
	isNowHold = true;
	renderer.drawBlock(hold_block, false);
}

void GameManager::shadowBlock(bool isNew)
{
	if(!isNew)
		renderer.eraseBlock(shadow_block);
	shadow_block = current_block;
	while (!board.strike_check(shadow_block)) {
		shadow_block.move(0, 1);
	}
	shadow_block.move(0, -1);
	renderer.drawBlock(shadow_block, true);
	if (monster.stage == 2 && rand()%35 == 0) {
		sm.playEffect("SoundEffects/gravity.wav");
		current_block = shadow_block;
		renderer.drawBlock(current_block, false);
	}
}

bool GameManager::checkState()
{
	if (isGameState == 2) {
		makeNewBlock();
		int temp = board.get_clear_line_score();
		if (temp != 0) {
			// 콤보 갱신
			if (comboTimer > 0) combo++; // 시간 안에 또 없앴다 → 콤보++
			else combo = 1;              // 콤보 초기화 후 시작

			comboTimer = 6;  // 콤보 유지 시간 (프레임 기준 약 2초)

			sm.playEffect("SoundEffects/line_clear.wav");
			if (monster.stage != 5) {
				monster.takeDamage(temp / 100);
				renderer.aniMonsterDamaged(monster);
				renderer.drawMonsterHp(monster);
				if (monster.isDead()) {
					monster.setMonsterShape(++monster.stage);
					++current_block.limit;

					if (monster.stage == 4) {
						//  여기서 바로 에필로그 보여주고 종료
						system("cls");

						vector<string> epilog = {
							"<에필로그>",
							" 이 이야기는 그린시러와 그린조아의 다툼으로 벌어진 이야기........",
							" 결국 그린시러를 물리친 그린조아...........",
							"하지만 원래세계로 돌아 갈 수 없다는 걸 안 것은 한참 뒤 이야기",
							" 새로운 테트리스 세계의 왕이 된 그린 조아. 이번엔 테트리스를 초록으로 물들여버린다."
						};

						renderer.printLineProlog(1, 10, epilog);

					
						isGameState = 0;
						return false;
					}

					system("cls");												
					renderer.drawMonsterTalk(monster);
					vector<string> lines = monster.getScriptLine(monster.stage);
					renderer.printLineAt(1, 15, lines);
					system("cls");
					renderer.drawBoard(board);
					renderer.eraseMonster(monster);
					renderer.drawMonster(monster);
					renderer.drawMonsterHp(monster);
					init();
					if (monster.stage == 4) {
						return false;
						isGameState = 0;
					}
				}
			}
		} else {
			// 줄을 못 없앴다면 콤보 타이머 감소
			if (comboTimer > 0) comboTimer--;
			else combo = 0;
		}
		if (monster.stage == 5) {
			// 점수 계산
			score += temp * monster.stage + combo * combo * temp;
			renderer.show_game_stat(score);
			if (combo > 0) {
				// 콤보 출력
				gotoxy(43, 13);
				cout << "COMBO: " << combo << "   ";
			}
		}
	}
	else if (isGameState == 1) {
		return false;
	}
	isGameState = 0;
	return true;
}



void GameManager::makeNewBlock()
{
	renderer.act_by_boss(monster, board);
	renderer.drawBoard(board);
	renderer.eraseBlock(next_block);
	current_block = next_block;
	current_block.setPos(5, 0);
	randType = static_cast<Tetromino>(rand() % 8);

	if(monster.stage == 0 && rand() % 3 == 0) randType = static_cast<Tetromino>(1);                            // 네모만 나오게 함
	else if (monster.stage == 0) randType = static_cast<Tetromino>(rand() % 7);

	if (monster.stage == 3) next_block.setGreenhateBlock(randType, monster.stage);
	else next_block.setBlock(randType, monster.stage);

	renderer.drawBlock(next_block, false);
	shadowBlock(true);
	renderer.drawBlock(current_block, false);
	isNowHold = false;
}
