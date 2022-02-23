#include "Gameplay.h"
#include"GameManager.h"
#include"EnlargePaddlePowerUp.h"

using namespace gamemanager;
namespace gamemanager
{

	namespace gameplay
	{
		extern bool gameOver = false;
		bool win;
		bool collide = false;
		bool isPowerUp1Picked;
		const int bricksPerColumn = 11;
		const int bricksPerRow = 5;
		float brickWidth = 61;
		float brickHeight = 30;
		float timer;
		int smashedBicksCount;
		int powerUpRandom;

		Ball* ball;
		Paddle* paddle;
		Brick* bricks[bricksPerColumn][bricksPerRow];
		EnlargePaddlePoweUp* powerUp1;
		void InitValues()
		{
			isPowerUp1Picked = false;
			timer = 0;
			smashedBicksCount = 0;
			powerUpRandom = 0;
			win = false;
			gameOver = false;
			ball = new Ball({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.87f }, { 300.0f,-300.0f }, 15, 15);
			paddle = new Paddle({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.9f }, 300.0f, 150, 10);
			powerUp1 = new EnlargePaddlePoweUp({ 0,0 }, 0.05f, 10, 10, false);
				for (int i = 0; i < bricksPerColumn; i++)
				{
					for (int j = 0; j < bricksPerRow; j++)
					{
						bricks[i][j] = new Brick(brickWidth, brickHeight, { (brickWidth * 1.2f) * i,(brickHeight * 1.2f) * j + 60 });
					}
				}


		}
		void UpdateFrame()
		{
			if (!gameOver)
			{
				ball->Update(paddle, collide);
				paddle->Update();
				if (powerUp1->GetIsActive())
				{
					
					powerUp1->Move();
					if (CheckCollisionRecs(Rectangle{ powerUp1->GetPos().x, powerUp1->GetPos().y, powerUp1->GetWidth(), powerUp1->GetHeight() }, Rectangle{ paddle->GetPos().x, paddle->GetPos().y, paddle->GetWidth(), paddle->GetHeight() }))
					{
						powerUp1->Collect(paddle);
						isPowerUp1Picked = true;
					}
					
				}
				if (isPowerUp1Picked)
				{
					timer += GetFrameTime();
				}
				if (timer>=10)
				{
					paddle->SetWidth(150);
					isPowerUp1Picked = false;
					powerUp1->SetIsActive(false);
					timer = 0;
				}
			
				for (int i = 0; i < bricksPerColumn; i++)
				{
					for (int j = 0; j < bricksPerRow; j++)
					{
						if (bricks[i][j]->GetIsActive())
						{
							bricks[i][j]->Update(ball);
							if (CheckCollisionRecs(Rectangle{ ball->GetPosition().x,ball->GetPosition().y,ball->GetWidth(),ball->GetHeight() }, Rectangle{ bricks[i][j]->GetPos().x,bricks[i][j]->GetPos().y,bricks[i][j]->GetWidth(),bricks[i][j]->GetHeight() }))
							{
								powerUpRandom = GetRandomValue(1, 20);
								if (powerUpRandom <= 15)
								{
									powerUp1->SetIsActive(true);
									powerUp1->SetPos(bricks[i][j]->GetPos());
									
									
								}
								smashedBicksCount++;
							}

						}
					}
				}

				CheckPause();
			}
			else
			{
				currentScreen = GAMEOVER;

			}
			if (smashedBicksCount >= bricksPerColumn * bricksPerRow)
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
			if (powerUp1->GetIsActive())
			{
				powerUp1->Draw();
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