#pragma once
#include "Renderer.h"
#include "SoundManager.h"

class Menu
{
public:
	Menu();
	void setPer(Renderer* renderer, SoundManager* sm);

	int getDifficulty() { return difficulty; }

	int menu();
	void option();
	void difficultySet();
	int stageSelect();
	int retrySelect();
private:
	Renderer* renderer;
	SoundManager* sm;

	short optionSelector;
	char keytemp;
	float volume;
	int difficulty;	// 0 : easy, 1 : normal, 2 : hard

};

