#pragma once
#include "Renderer.h"
#include "SoundManager.h"

class Menu
{
public:
	Menu();
	void setPer(Renderer* renderer, SoundManager* sm);
	int getMenuSelector() { return menuSelector; }
	int getDifficulty() { return difficulty; }
	int getStageSelected() { return stageSelector; }

	void menu();
	void option();
	void difficultySet();
	void stageSelect();
	int printRetryWIthChoices();
private:
	Renderer* renderer;
	SoundManager* sm;

	short menuSelector;
	short optionSelector;
	short stageSelector;
	char keytemp;
	float volume;
	int difficulty;	// 0 : easy, 1 : normal, 2 : hard

};

