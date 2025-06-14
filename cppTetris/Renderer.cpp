﻿#include "Renderer.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;


void gotoxy(int x, int y) {
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(Color color) {
	static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, static_cast<int>(color));
}

Renderer::Renderer()
{
	// 메뉴에 들어갈 string 할당
	menu_string = { "Start", "Option", "Exit" };
	option_string = { "Stage", "Volume", "Apply" };
	difficulty_string = { "Easy", "Normal", "Hard" };
	stage_string = { "Story", "Stage 1", "Stage 2", "Stage 3", "Boss", "무한 모드", "Back"};
	retry_string = { "Retry", "Back To Menu" };

	system("Tetris");
	system("mode con:cols=100 lines=30");
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = false;
	ConsoleCursor.dwSize = 1;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void Renderer::show_logo()
{
	cout << endl;
	std::vector<std::vector<std::string>> logo = {
		// M
		{
			" __  __ ",
			"|  \\/  |",
			"| \\  / |",
			"| |\\/| |",
			"| |  | |",
			"|_|  |_|"
		},
		// O
		{
			"  ____  ",
			" / __ \\ ",
			"| |  | |",
			"| |  | |",
			"| |__| |",
			" \\____/ "
		},
		// N
		{
			" _   _ ",
			"| \\ | |",
			"|  \\| |",
			"| . ` |",
			"| |\\  |",
			"|_| \\_|"
		},
		// S
		{
			"  _____ ",
			" / ____|",
			"| (___  ",
			" \\___ \\ ",
			" ____) |",
			"|_____/ "
		},
		// T
		{
			" _______ ",
			"|__   __|",
			"   | |   ",
			"   | |   ",
			"   | |   ",
			"   |_|   "
		},
		// R
		{
			" _____  ",
			"|  __ \\ ",
			"| |__) |",
			"|  _  / ",
			"| | \\ \\ ",
			"|_|  \\_\\"
		},
		// I
		{
			" _____ ",
			"|_   _|",
			"  | |  ",
			"  | |  ",
			" _| |_ ",
			"|_____|"
		},
		// S
		{
			"  _____ ",
			" / ____|",
			"| (___  ",
			" \\___ \\ ",
			" ____) |",
			"|_____/ "
		}
	};

	for (int i = 0; i < logo.size(); i++) {
		for (int j = 0; j < logo[0].size(); j++) {
			gotoxy(22 + 8 * i, 3 + j);
			SetColor(static_cast<Color>(i + 1));
			cout << logo[i][j];
		}
	}
	gotoxy(45, 10);
	cout << "-그린조아의 대 모험-";
}

void Renderer::show_game_stat(int score)
{
	cout << endl;
	
	SetColor(Color::GRAY);

	
	
	gotoxy(ab_x + 28, ab_y + 9);
	cout << "SCORE";

	

	// 점수는 계속 업데이트됨
	gotoxy(ab_x + 28, ab_y + 10);
	printf("%10d", score);
}

void Renderer::drawMonster(Monster& mon)
{
	cout << endl;
	monsterVec monster = mon.getMonsterVec();
	for (int i = 0; i < monster.size(); i++) {
		gotoxy(65, 8 + i);
		cout << monster[i];
	}
	gotoxy(85, 27);
}

void Renderer::drawMonsterTalk(Monster& mon)
{
	cout << endl;
	monsterVec monster = mon.getMonsterVec();
	for (int i = 0; i < monster.size(); i++) {
		gotoxy(40, 2 + i);
		cout << monster[i];
	}
	gotoxy(77, 23);
}



void Renderer::drawMonsterHp(Monster& mon)
{
	static int prevHp = -1; // 이전 HP 저장 (초기값 -1로 설정)
	int hp = mon.getCurrentHp();
	int maxHp = mon.getMaxHp();

	SetColor(Color::WHITE);
	// HP 텍스트 갱신
	gotoxy(65, 15);
	cout << "                             ";
	gotoxy(65, 15);
	cout << "HP : " << hp << " / " << maxHp;

	/*for (int i = maxHp; i > 0; i--) {
		gotoxy(60 + i * 2, 6);
		Sleep(50);
		if (i <= hp)
			cout << "■";
		else*/


 	// 처음이거나 체력 증가일 경우 바로 출력
 	if (prevHp == -1 || hp >= prevHp) {
 		for (int i = 0; i < maxHp; i++) {
 			gotoxy(65 + i * 2, 16);
 			if (i < hp)
 				cout << "■";
 			else
 				cout << "□";
 		}
 	}
 	// 체력 감소일 경우 부드럽게 감소 효과
 	else {
 		for (int i = prevHp - 1; i >= hp; i--) {
 			gotoxy(65 + i * 2, 16);

			cout << "□";
			Sleep(50); // 50ms 딜레이 (너무 느리면 30으로 줄여도 됨)
		}
	}
}

void Renderer::aniMonsterDamaged(Monster& mon)
{
	for (int i = 0; i < 5; i++) {
		if (i % 2 == 0) SetColor(Color::WHITE);
		else SetColor(Color::RED);
		Sleep(100);
		drawMonster(mon);
	}
}

void Renderer::eraseMonster(Monster& mon)
{
	cout << endl;
	monsterVec monster = mon.getMonsterVec();
	for (int i = 0; i < monster.size(); i++) {
		for (int j = 0; j < monster[i].size(); j++) {
			gotoxy(60 + j, 10 + i);
			cout << " ";
		}
	}
	gotoxy(77, 23);
}

void Renderer::act_by_boss(Monster& mon, Board& board)
{
	int attack_row = 1;
	int empty_place = rand() % 12 + 1;
	if (rand() % 100 < 10 * mon.getStage()) {
		board.result_by_attack(empty_place);
	}
}





void Renderer::show_menu(short menu)
{
	cout << endl;
	for (size_t i = 0; i < 3; i++) {
		gotoxy(50, 20 + i);
		if (menu == i) {
			SetColor(Color::YELLOW);
			cout << "▶";
		}
		else
			SetColor(Color::WHITE);
		cout << menu_string[i] << "     ";
	}

	SetColor(Color::WHITE);
	gotoxy(77, 23);
}


void Renderer::drawOption(short optionSelector, float volume, int difficulty)
{
	cout << endl;
	for (size_t i = 0; i < option_string.size(); i++) {
		gotoxy(50, (i == 2 ? 15 : 10 + i));
		if (optionSelector == i) {
			SetColor(Color::YELLOW);
			cout << "▶";
		}
		else
			SetColor(Color::WHITE);
		cout << option_string[i] << "  ";

		if (i == 0) {
			gotoxy(60, 10);

			cout << "◀ " << difficulty_string[difficulty] << " ▶   ";
		}
		else if (i == 1) {
			gotoxy(60, 11);
			cout << "◀ " << volume << " ▶   ";
		}


	}

	SetColor(Color::WHITE);
	gotoxy(77, 23);
}

void Renderer::drawStageSelect(short stageSelector)
{
	cout << endl;
	for (size_t i = 0; i < stage_string.size(); i++) {
		gotoxy(46, i != 6 ? 10 + i : 20);
		if (stageSelector == i) {
			SetColor(Color::YELLOW);
			cout << "▶";
		}
		else
			SetColor(Color::WHITE);
		cout << stage_string[i] << "    ";
	}

}

void Renderer::drawGameOverFrame()
{
	cout << endl;
	SetColor(Color::WHITE);
	gotoxy(40, 10);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	gotoxy(40, 11);
	cout << "┃**************************┃";
	gotoxy(40, 12);
	cout << "┃*        GAME OVER       *┃";
	gotoxy(40, 13);
	cout << "┃**************************┃";
	gotoxy(40, 14);
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
	
}

void Renderer::drawGameOver(short selector)
{
	cout << endl;
	for (int i = 0; i < retry_string.size(); i++) {
		gotoxy(40 + i * 8, 16);
		if (i == selector) {
			SetColor(Color::YELLOW);
			cout << "▶";
		}
		else
			SetColor(Color::WHITE);
		cout << retry_string[i] << "   ";
	}
}

// 약간의 개선이 필요할듯
void Renderer::drawBlock(Block& block, bool isShadow)
{
	cout << endl;
	setBlockColor(block);
	SetColor(color);
	short x = block.getX();
	short y = block.getY();
	gotoxy(x, y);
	shapeVec shape = block.getShape();

	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] != 0) {
				gotoxy((x + j) * 2 + ab_x, y + i + ab_y);
				cout << (isShadow ? "□" : "■");
			}

		}
	}

	SetColor(Color::WHITE);
	gotoxy(77, 23);
}

void Renderer::eraseBlock(Block& block)
{
	cout << endl;
	short x = block.getX();
	short y = block.getY();
	shapeVec shape = block.getShape();
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] != 0) {
				gotoxy((x + j) * 2 + ab_x, y + i + ab_y);
				cout << "  ";
			}

		}
	}
}

void Renderer::nextBlockFrame()
{
	SetColor(Color::DARK_SKY_BLUE);
	for (int i = 1; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			gotoxy(ab_x + 30 + j * 2, i);
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				printf("■");
			}
			else {
				printf("  ");
			}

		}
	}
}

void Renderer::holdBlockFrame()
{
	SetColor(Color::DARK_SKY_BLUE);
	for (int i = 1; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			gotoxy(j * 2, i);
			if (i == 1 || i == 6 || j == 0 || j == 5)
			{
				printf("■");
			}
			else {
				printf("  ");
			}

		}
	}
}
void Renderer::setBlockColor(Block& block) {
	if (block.getType() == Tetromino::B) {
		color = getColorFromType(static_cast<Tetromino>(block.getShape()[0][0] - 1));
	}
	else {
		color = getColorFromType(block.getType());
	}
	SetColor(color);
}

Color Renderer::getColorFromType(Tetromino type) {
	switch (type)
	{
	case Tetromino::I: return Color::GREEN;
	case Tetromino::O: return Color::YELLOW;
	case Tetromino::T: return Color::VOILET;
	case Tetromino::J: return Color::BLUE;
	case Tetromino::L: return Color::DARK_YELLOW;
	case Tetromino::S: return Color::SKY_BLUE;
	case Tetromino::Z: return Color::RED;
	default: return Color::GRAY;
	}
}

void Renderer::drawBoard(Board& board)
{
	cout << endl;
	for (size_t i = 0; i < Board::height; i++) {
		for (size_t j = 0; j < Board::width; j++) {

			gotoxy((j * 2) + ab_x, i + ab_y);
			if (j == 0 || j == Board::width - 1 || i == Board::height - 1) {
				SetColor(Color::WHITE);
				cout << ((i < 3) ? "□" : "■");
			}
			else if (board.board[i][j] != 0) {
				SetColor(getColorFromType(static_cast<Tetromino>(board.board[i][j] - 1)));
				cout << "■";
			}
			else
				cout << "   ";
		}
	}

	SetColor(Color::BLACK);
	gotoxy(77, 23);
}

void Renderer::printLineAt(int x, int y, const vector<string> lines) {
	for (const auto& line : lines) {
		// 기존 출력된 내용 지우기
		gotoxy(x, y - 1);
		cout << "                                                                                     ";

		gotoxy(x, y);
		cout << "                                                                                     ";

		gotoxy(x, y + 1);
		cout << "                                                                                     ";

		gotoxy(x, y + 2);
		cout << "                                                                                     ";

		gotoxy(x, y + 3);
		cout << "                                                                                     ";

		gotoxy(x, y + 4);
		cout << "                                                                                     ";

		// 윗테두리
		gotoxy(x, y - 1);
		cout << "+------------------------------------------------------------------------------------+";

		// 본문 출력
		gotoxy(x, y);
		cout << "| " << string(100, ' ') << " |";  // 공간 확보
		gotoxy(x + 2, y);
		cout << line;

		gotoxy(x, y + 1);
		cout << "| " << "                                                                                  " << " |";

		gotoxy(x, y + 2);
		cout << "| " << "                                                                                  " << " |";

		gotoxy(x, y + 3);
		cout << "| " << "                                                                                  " << " |";

		// 아래 테두리
		gotoxy(x, y + 4);
		cout << "+------------------------------------------------------------------------------------+";

		_getch();  // 아무 키 입력

		gotoxy(x, y - 1);
		cout << "                                                                                       ";

		gotoxy(x, y);
		cout << "                                                                                       ";

		gotoxy(x, y + 1);
		cout << "                                                                                       ";

		gotoxy(x, y + 2);
		cout << "                                                                                       ";

		gotoxy(x, y + 3);
		cout << "                                                                                       ";

		gotoxy(x, y + 4);
		cout << "                                                                                       ";
	}
}


void Renderer::printLineProlog(int x, int y, const vector<string> lines) {
	// 윗테두리 출력
	gotoxy(x, y - 1);
	cout << "+------------------------------------------------------------------------------------------------+";

	// 아래 테두리 출력
	gotoxy(x, y + lines.size());
	cout << "+------------------------------------------------------------------------------------------------+";

	for (size_t i = 0; i < lines.size(); ++i) {
		gotoxy(x, y + i);
		cout << "| " << string(100, ' ') << " |";  // 공간 확보

		gotoxy(x + 2, y + i);  // 실제 텍스트 위치
		for (char ch : lines[i]) {
			cout << ch;
			Sleep(1);
		}
	}

	_getch();  // 아무 키 입력
}
