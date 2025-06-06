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
	menu.menu();
	int menuSelector = menu.getMenuSelector();
	if (menuSelector == 0) {
		menu.stageSelect();
		monster.stage = -1;
		switch (menu.getStageSelected())
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
			monster.setMonsterShape(1);
			play();
			break;
		case 3:		// 3 Stage
			monster.stage = 2;
			monster.setMonsterShape(2);
			play();
			break;
		case 4:		// Boss
			monster.stage = 3;
			monster.setMonsterShape(3);
			play();
			break;
		case 5:		// 무한모드
			break;
		case 6:		// back
			return;

		}
	}
	else if (menuSelector == 1) {
		menu.option();
	}
	else if (menuSelector == 2) {
		exit(0);
	}
}

void GameManager::play()
{	
	if (monster.stage == -1) {
		vector<string> prolog = { "<프롤로그>",
			" 이 이야기는 그린시러와 그린조아의 다툼으로 벌어집니다.",
			" 테트로니아는 블록들로 이루어진 세계로, 평소엔 조화롭게 돌아가지만,",
			"그린시러의 영향으로 특정 블록들이 자의식을 얻어 제멋대로 움직이며 세계의 균형을 위협하기 시작합니","다.",
			"  이 블록들을 통제할 수 있는 유일한 사람은 전설의 \"테트리스 마스터\"뿐!" };
		renderer.printLineProlog(1, 10, prolog);
		system("cls");
		monster.stage = 0;
	}
	
	

	renderer.drawMonsterTalk(monster);

	vector<string> lines = monster.getScriptLine(monster.stage);
	renderer.printLineAt(1, 15, lines);


	system("cls");

	// 테스트용 몬스터
	renderer.drawMonster(monster);
	renderer.drawMonsterHp(monster);

	
	init();
	int i = 0;
	score = 0;
	renderer.show_game_stat(score);

	
	while (true) {
		while (checkState()) {

			input();
			if (i % (30 - 12 * menu.getDifficulty()) == 0) {
				update();
			}
			i++;
			Sleep(15);
			gotoxy(77, 23);

		}
		system("cls");
		int select = menu.printRetryWIthChoices();
		if (select == 0) {
			system("cls");

		}
	}
}

void GameManager::init()
{
	renderer.drawBoard(board);
	renderer.nextBlockFrame();
	renderer.holdBlockFrame();
	isHold = false;
	isGameState = 0;
	randType = static_cast<Tetromino>(rand() % 7);
	if (monster.stage == 0 && rand()% 3 == 0) randType = static_cast<Tetromino>(1);										// 네모 블록
	
	current_block.setBlock(randType);

	if (monster.stage == 3) {																			// 초록 블록
		randType = static_cast<Tetromino>(rand() % 7);
		current_block.setGreenhateBlock(randType);
	}

	current_block.setPos(5, 0);
	randType = static_cast<Tetromino>(rand() % 7);
	if(monster.stage == 0 && rand()%3 == 0) randType = static_cast<Tetromino>(1);										// 네모 블록
	
	next_block.setBlock(randType);

	if (monster.stage == 3) {																			// 초록 블록
		randType = static_cast<Tetromino>(rand() % 7);
		next_block.setGreenhateBlock(randType);
	}

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
	//renderer.drawBoard(board);
	renderer.eraseBlock(current_block);
	isGameState = board.move_block(current_block);

	renderer.drawBlock(current_block, false);
	checkState();
}

void GameManager::moveRotate()
{
	renderer.eraseBlock(current_block);
	/*if (monster.stage == 2) {																		// 방향 못바꾸게 하는건데 일단 주석 처리
		int x = current_block.getPosX();
		int y = current_block.getPosY();
		randType = static_cast<Tetromino>(rand() % 7);
		current_block.setBlock(randType);
		current_block.setPos(x, y);
	}*/
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
		Tetromino temp = current_block.getType();
		hold_block.setBlock(temp);
	
		makeNewBlock();
		isHold = true;
		
	}
	else{
		renderer.eraseBlock(hold_block);
		renderer.eraseBlock(current_block);
		Tetromino temp;
		temp = current_block.getType();
		current_block = hold_block;
		current_block.setPos(5, 0);

		hold_block.setBlock(temp);


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
		// create New Block
		makeNewBlock();
		// 몬스터에 데미지가 들어가면 업데이트
		int temp = board.get_clear_line_score();
		if (temp != 0) {
			// 테스트 용으로 넣어놓은 코드
	
			sm.playEffect("SoundEffects/line_clear.wav");
			monster.takeDamage(temp / 100);
			renderer.aniMonsterDamaged(monster);
			renderer.drawMonsterHp(monster);
			if (monster.isDead()) {
				monster.getNextMonster();

				system("cls");

				renderer.drawMonsterTalk(monster);

				vector<string> lines = monster.getScriptLine(++monster.stage);
				renderer.printLineAt(1, 15, lines);

				system("cls");

				renderer.drawBoard(board);
				
				renderer.drawMonsterHp(monster);
				renderer.eraseMonster(monster);

				renderer.drawMonster(monster);
				renderer.drawMonsterHp(monster);
				init();
			}
			
		}
		score += temp*monster.stage;
		renderer.show_game_stat(score);
	}
	else if (isGameState == 1) {
		                                                           // 몬스터 죽으면 스테이지 업
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
	randType = static_cast<Tetromino>(rand() % 7);
	if(monster.stage == 0 && rand() % 3 == 0) randType = static_cast<Tetromino>(1);                            // 네모만 나오게 함
	next_block.setBlock(randType);
	if (monster.stage == 3 ) {
		randType = static_cast<Tetromino>(rand() % 7);
		next_block.setGreenhateBlock(randType);
	}
	renderer.drawBlock(next_block, false);
	shadowBlock(true);
	renderer.drawBlock(current_block, false);
	isNowHold = false;
}
