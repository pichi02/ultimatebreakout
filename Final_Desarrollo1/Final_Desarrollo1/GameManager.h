#pragma once
namespace gamemanager
{
	enum SCREENS
	{
		MENU = 0, GAMEPLAY, GAMEOVER, CREDITS, PAUSE
	};

	extern bool exit;
	extern SCREENS currentScreen;

	void ExecuteGame();
}