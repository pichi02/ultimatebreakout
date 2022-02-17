#include "Gameplay.h"
#include"GameManager.h"

using namespace gamemanager;
namespace gamemanager
{

	namespace gameplay
	{
		extern bool gameOver = false;
		bool collide = false;
		const int bricksPerColumn = 11;
		const int bricksPerRow = 5;
		float brickWidth = 61;
		float brickHeight = 30;


		Ball* ball;
		Paddle* paddle;
		Brick* bricks[bricksPerColumn][bricksPerRow];

		void InitValues()
		{
			gameOver = false;
			ball = new Ball({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.87f }, { 300.0f,-300.0f }, 15,15);
			paddle = new Paddle({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.9f }, 300.0f, 150, 10);
			for (int i = 0; i < bricksPerColumn; i++)
			{
				for (int j = 0; j < bricksPerRow; j++)
				{
					bricks[i][j] = new Brick(brickWidth, brickHeight, { (brickWidth * 1.2f) * i,(brickHeight * 1.2f) * j + 30 });
				}
			}
			/*	InitBricks();*/

		}
		void UpdateFrame()
		{
			if (!gameOver)
			{
				ball->Update(paddle, collide);
				paddle->Update();
				for (int i = 0; i < bricksPerColumn; i++)
				{
					for (int j = 0; j < bricksPerRow; j++)
					{
						bricks[i][j]->Update(ball);
					}
				}
				CheckPause();
			}
			else
			{
				currentScreen = GAMEOVER;

			}

			gameOver = GameOver();
		}
		void Draw()
		{
			ClearBackground(BLACK);

			for (int i = 0; i < bricksPerColumn; i++)
			{
				for (int j = 0; j < bricksPerRow; j++)
				{
					if (bricks[i][j]->GetIsActive())
					{
						bricks[i][j]->Draw();
					}

				}
			}

			paddle->Draw();
			ball->Draw();
		}
		void ResetValues()
		{
			InitValues();
		}
		void UnloadGameplay()
		{
		}
		bool GameOver()
		{
			return ball->GetPosition().y >= GetScreenHeight();;
		}
		void CheckPause()
		{
			if (IsKeyPressed('P'))
			{
				currentScreen = PAUSE;
			}
		}

	}
}