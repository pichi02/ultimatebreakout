#include "Gameplay.h"
#include"GameManager.h"
#include"EnlargePaddlePowerUp.h"
#include"ShootsPowerUp.h"

using namespace gamemanager;
namespace gamemanager
{

	namespace gameplay
	{
		extern bool gameOver = false;
		bool win;
		bool collide = false;
		bool isPowerUp1Picked;
		bool isPowerUp2Picked;
		const int bricksPerColumn = 11;
		const int bricksPerRow = 5;
		float brickWidth = 61;
		float brickHeight = 30;
		float timer;
		float powerUp1Timer;
		float powerUp2Timer;
		int smashedBicksCount;
		int powerUpRandom;

		Ball* ball;
		Paddle* paddle;
		Brick* bricks[bricksPerColumn][bricksPerRow];
		EnlargePaddlePowerUp* powerUp1;
		ShootsPowerUp* powerUp2;

		void InitValues()
		{
			timer = 0;
			isPowerUp1Picked = false;
			isPowerUp2Picked = false;
			powerUp1Timer = 0;
			powerUp1Timer = 0;
			smashedBicksCount = 0;
			powerUpRandom = 0;
			win = false;
			gameOver = false;
			ball = new Ball({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.87f }, { 150.0f,-150.0f }, 15, 15);
			paddle = new Paddle({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.9f }, 300.0f, 140, 10);
			powerUp1 = new EnlargePaddlePowerUp({ 0,0 }, 0.05f, 10, 10, false);
			powerUp2 = new ShootsPowerUp({ 0,0 }, 0.05f, 10, 10, false, paddle);
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
				/*powerUp2->Collect(paddle);*/

				timer += GetFrameTime();
				if ((int)timer % 10 == 0)
				{
					ball->IncreaseSpeed();
				}
				ball->Update(paddle, collide);
				paddle->Update();
				if (powerUp1->GetIsActive() && !isPowerUp1Picked)
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
					powerUp1Timer += GetFrameTime();
				}
				if (powerUp2->GetIsActive() && !isPowerUp2Picked)
				{

					powerUp2->Move();
					if (CheckCollisionRecs(Rectangle{ powerUp2->GetPos().x, powerUp2->GetPos().y, powerUp2->GetWidth(), powerUp2->GetHeight() }, Rectangle{ paddle->GetPos().x, paddle->GetPos().y, paddle->GetWidth(), paddle->GetHeight() }))
					{

						isPowerUp2Picked = true;

					}

				}
				if (isPowerUp2Picked && powerUp2Timer < 10)
				{
					powerUp2->Collect(paddle);
					powerUp2Timer += GetFrameTime();
					for (int i = 0; i < bricksPerColumn; i++)
					{
						for (int j = 0; j < bricksPerRow; j++)
						{
							powerUp2->CheckShootAndBrickCollision(bricks[i][j], smashedBicksCount);
						}
					}
				}
				else if (powerUp2Timer >= 10)
				{
					isPowerUp2Picked = false;
					powerUp2->SetIsActive(false);
					powerUp2Timer = 0;
					powerUp2->TurnOffShoots();
				}

				if (powerUp1Timer >= 10)
				{
					paddle->SetWidth(150);
					isPowerUp1Picked = false;
					powerUp1->SetIsActive(false);
					powerUp1Timer = 0;
				}

				for (int i = 0; i < bricksPerColumn; i++)
				{
					for (int j = 0; j < bricksPerRow; j++)
					{
						/*powerUp2->CheckShootAndBrickCollision(bricks[i][j], smashedBicksCount);*/
						if (bricks[i][j]->GetIsActive())
						{
							bricks[i][j]->Update(ball);
							if (CheckCollisionRecs(Rectangle{ ball->GetPosition().x,ball->GetPosition().y,ball->GetWidth(),ball->GetHeight() }, Rectangle{ bricks[i][j]->GetPos().x,bricks[i][j]->GetPos().y,bricks[i][j]->GetWidth(),bricks[i][j]->GetHeight() }))
							{
								powerUpRandom = GetRandomValue(1, 20);
								if (powerUpRandom >= 15)
								{
									powerUp1->SetIsActive(true);
									powerUp1->SetPos(bricks[i][j]->GetPos());

								}
								else if (powerUpRandom >= 0 && powerUpRandom < 15)
								{
									powerUp2->SetIsActive(true);
									powerUp2->SetPos(bricks[i][j]->GetPos());
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
			if (powerUp1->GetIsActive() && !isPowerUp1Picked)
			{
				powerUp1->Draw();
			}
			if (powerUp2->GetIsActive() && !isPowerUp2Picked)
			{
				powerUp2->Draw();
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