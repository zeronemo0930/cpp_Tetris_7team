#include "Menu.h"
#include <conio.h>
#include <thread>   
#include <chrono> 
#include <cstdlib>

#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50
#define KEY_ENTER       0x0D
using namespace std;


Menu::Menu() : keytemp(NULL), menuSelector(0), optionSelector(0), volume(20), difficulty(0),
stageSelector(0), renderer(nullptr), sm(nullptr)
{
}

void Menu::setPer(Renderer* renderer, SoundManager* sm)
{
	this->renderer = renderer;
}

void Menu::menu() {
	menuSelector = 0;
	renderer->show_logo();
	renderer->show_menu(menuSelector);
	while (true) {

		if (_kbhit()) {
			keytemp = _getch();
			if (keytemp == EXT_KEY) {
				keytemp = _getch();
				switch (keytemp)
				{
				case KEY_UP:
					if (menuSelector > 0) {
						menuSelector--;
						renderer->show_menu(menuSelector);
						sm->playEffect("SoundEffects/menu.wav");
					}
					break;
				case KEY_DOWN:
					if (menuSelector < 2) {
						menuSelector++;
						renderer->show_menu(menuSelector);
						sm->playEffect("SoundEffects/menu.wav");
					}
					break;
				}
			}
			if (keytemp == '\r') {
				sm->playEffect("SoundEffects/menu.wav");
				break;
			}
		}
	}

	system("cls");
	return;
}

void Menu::option()
{
	optionSelector = 0;
	renderer->drawOption(optionSelector, volume, difficulty);
	while (true) {

		if (_kbhit()) {
			keytemp = _getch();
			if (keytemp == EXT_KEY) {
				keytemp = _getch();
				switch (keytemp)
				{
				case KEY_UP:
					if (optionSelector > 0) {
						optionSelector--;
						renderer->drawOption(optionSelector, volume, difficulty);
						sm->playEffect("SoundEffects/menu.wav");
					}
					break;
				case KEY_DOWN:
					if (optionSelector < 2) {
						optionSelector++;
						renderer->drawOption(optionSelector, volume, difficulty);
						sm->playEffect("SoundEffects/menu.wav");
					}
					break;
				case KEY_LEFT:
					if (optionSelector == 0) {
						difficultySet();
					}
					else if (optionSelector == 1) {
						if (volume > 0) {
							volume--;
							renderer->drawOption(optionSelector, volume, difficulty);
							sm->playEffect("SoundEffects/menu.wav");
						}
					}
					break;

				case KEY_RIGHT:
					if (optionSelector == 0) {
						difficultySet();
					}
					else if (optionSelector == 1) {
						if (volume < 100) {
							volume++;
							renderer->drawOption(optionSelector, volume, difficulty);
							sm->playEffect("SoundEffects/menu.wav");
						}

					}
					break;
				}
			}
			if (keytemp == '\r') {
				if (optionSelector == 2) {
					sm->playEffect("SoundEffects/menu.wav");
					sm->SetMasterVolume(volume);
					break;
				}
			}
		}
	}
	system("cls");
	return;
}

void Menu::difficultySet()
{
	difficulty++;
	difficulty %= 3;
	sm->playEffect("SoundEffects/menu.wav");
	renderer->drawOption(optionSelector, volume, difficulty);
}

void Menu::stageSelect()
{
	stageSelector = 0;
	renderer->drawStageSelect(stageSelector);
	while (true) {
		if (_kbhit()) {
			keytemp = _getch();
			if (keytemp == EXT_KEY) {
				keytemp = _getch();
				switch (keytemp)
				{
				case KEY_UP:
					if (stageSelector > 0) {
						stageSelector--;
						renderer->drawStageSelect(stageSelector);
						sm->playEffect("SoundEffects/menu.wav");
					}
					break;
				case KEY_DOWN:
					if (stageSelector < 6) {
						stageSelector++;
						renderer->drawStageSelect(stageSelector);
						sm->playEffect("SoundEffects/menu.wav");
					}
					break;
				}
			}
			if (keytemp == '\r') {
				sm->playEffect("SoundEffects/menu.wav");
				break;
			}
		}
	}
	system("cls");
	return;
}

void Menu::printRetryWIthChoices() {
	int x = 0;
	int y = 20;


	vector<string> lines = {
		"게임이 끝났습니다. 다시 도전하시겠습니까?"
	};

	vector<string> choices = {
		"다시 하기",
		"메인 메뉴로",
		"게임 그만두기"
	};

	const int width = 94;
	const string border = "+" + string(width, '-') + "+";

	// 텍스트 출력
	gotoxy(x, y - 1);
	cout << border;

	for (size_t i = 0; i < lines.size(); ++i) {
		gotoxy(x, y + i);
		cout << "| " << string(width - 2, ' ') << " |";
		gotoxy(x + 2, y + i);
		for (char ch : lines[i]) {
			cout << ch;

		}
	}
	gotoxy(x, y + lines.size());
	cout << border;

	// 선택지 처리
	int selected = 0;
	bool running = true;

	while (running) {
		for (size_t i = 0; i < choices.size(); ++i) {
			gotoxy(x + 4, y + static_cast<int>(lines.size()) + 2 + i);
			if (i == selected) cout << "> ";
			else cout << "  ";
			cout << choices[i] << "       ";
		}

		int ch = _getch();
		if (ch == 224) {
			ch = _getch();
			if (ch == KEY_UP && selected > 0) selected--;
			else if (ch == KEY_DOWN && selected < static_cast<int>(choices.size()) - 1) selected++;
		}
		else if (ch == KEY_ENTER) {
			running = false;
		}
	}

	// 결과 확인용 (예: 나중엔 이 값 리턴 가능)
	gotoxy(x + 2, y + static_cast<int>(lines.size()) + static_cast<int>(choices.size()) + 4);
	cout << "선택됨: " << choices[selected];
	cin.get();
}

