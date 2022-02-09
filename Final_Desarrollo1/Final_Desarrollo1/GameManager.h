#pragma once
#include "Gameplay.h"
namespace gamemanager
{
	using namespace gameplay;
	enum SCREENS
	{
		MENU = 0, GAMEPLAY, GAMEOVER, CREDITS, PAUSE
	};

	extern bool exit;
	extern SCREENS currentScreen;

	void ExecuteGame();
}