#pragma once
#include"raylib.h"
namespace gamemanager
{
	namespace gameplay
	{
		void InitValues();
		void UpdateFrame();
		void Draw();
		void ResetValues();
		void UnloadGameplay();
		void DrawPaddle();
		void UpdatePaddle();
		extern bool gameOver;
	}
}