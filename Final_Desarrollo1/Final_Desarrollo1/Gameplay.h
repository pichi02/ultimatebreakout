#pragma once
#include"raylib.h"
namespace gamemanager
{
	namespace gameplay
	{
		extern bool gameOver;
		void InitValues();
		void UpdateFrame();
		void Draw();
		void ResetValues();
		void UnloadGameplay();
		void DrawPaddle();
		void UpdatePaddle();
		void UpdateBall();
		void DrawBall();
		void CheckBallAndPaddleCollision();
		bool GameOver();
		void InitBricks();
		void DrawBricks();
		void BricksAndBallCollision();
		void UpdateBall1();
	}
}