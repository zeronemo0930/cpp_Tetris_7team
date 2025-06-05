#include "Menu.h"
#include <conio.h>
#include <cstdlib>

#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

using namespace std;


Menu::Menu() : menuSelector(0), optionSelector(0), volume(20), difficulty(0)
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
