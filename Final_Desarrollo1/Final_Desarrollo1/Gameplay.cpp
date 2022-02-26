#include "Gameplay.h"
#include"GameManager.h"
#include"EnlargePaddlePowerUp.h"
#include"ShootsPowerUp.h"
#include"FloorPowerUp.h"

using namespace gamemanager;
namespace gamemanager
{

	namespace gameplay
	{
		extern bool gameOver = false;
		bool win;
		bool ballAndPaddleCollide = false;
		bool ballAndWallXCollide;
		bool ballAndWallYCollide;
		bool isPowerUp1Picked;
		bool isPowerUp2Picked;
		bool isPowerUp3Picked;
		bool resetLevel = true;
		const int bricksPerColumn = 11;
		const int bricksPerRow = 5;
		float brickWidth = 61;
		float brickHeight = 30;
		float timer;
		float powerUp1Timer;
		float powerUp2Timer;
		float powerUp3Timer;
		int smashedBicksCount;
		int powerUpRandom;
		int lastPowerUpRandom;
		int lifes;
		float ballSpeedX;

		Ball* ball;
		Paddle* paddle;
		Brick* bricks[bricksPerColumn][bricksPerRow];
		EnlargePaddlePowerUp* powerUp1;
		ShootsPowerUp* powerUp2;
		FloorPowerUp* powerUp3;

		void InitValues()
		{
			if (resetLevel)
			{
				lifes = 3;
				smashedBicksCount = 0;
				for (int i = 0; i < bricksPerColumn; i++)
				{
					for (int j = 0; j < bricksPerRow; j++)
					{
						bricks[i][j] = new Brick(brickWidth, brickHeight, { (brickWidth * 1.2f) * i,(brickHeight * 1.2f) * j + 60 });
					}
				}
			}

			timer = 0;
			isPowerUp1Picked = false;
			isPowerUp2Picked = false;
			isPowerUp3Picked = false;
			ballAndWallXCollide = false;
			ballAndWallYCollide = false;
			powerUp1Timer = 0;
			powerUp1Timer = 0;
			powerUp3Timer = 0;
			powerUpRandom = 0;
			lastPowerUpRandom = 0;
			win = false;
			gameOver = false;
			int rand = GetRandomValue(1, 10);
			if (rand<=5)
			{
				ballSpeedX = 150.0f;
			}
			else
			{
				ballSpeedX = -150.0f;
			}
			ball = new Ball({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.87f }, { ballSpeedX,-150.0f }, 15, 15);
			paddle = new Paddle({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.9f }, 300.0f, 140, 10);
			powerUp1 = new EnlargePaddlePowerUp({ 0,0 }, 150.0f, 10, 10, false);
			powerUp2 = new ShootsPowerUp({ 0,0 }, 150.0f, 10, 10, false, paddle);
			powerUp3 = new FloorPowerUp({ 0,0 }, 150.0f, 10, 10, false, Rectangle{ 0,GetScreenHeight() * 0.93f,(float)GetScreenWidth(),10.0f });

			resetLevel = false;

		}
		void UpdateFrame()
		{
			if (!gameOver)
			{


				timer += GetFrameTime();
				if ((int)timer % 10 == 0)
				{
					ball->IncreaseSpeed();
				}
				ball->Update(paddle, ballAndPaddleCollide, ballAndWallXCollide, ballAndWallYCollide);
				paddle->Update();
				if (powerUp1->GetIsActive() && !isPowerUp1Picked)
				{

					powerUp1->Move();
					if (CheckCollisionRecs(Rectangle{ powerUp1->GetPos().x, powerUp1->GetPos().y, powerUp1->GetWidth(), powerUp1->GetHeight() }, Rectangle{ paddle->GetPos().x, paddle->GetPos().y, paddle->GetWidth(), paddle->GetHeight() }))
					{
						isPowerUp1Picked = true;
						powerUp1->Collect(paddle, ball);
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
				if (powerUp3->GetIsActive() && !isPowerUp3Picked)
				{

					powerUp3->Move();
					if (CheckCollisionRecs(Rectangle{ powerUp3->GetPos().x, powerUp3->GetPos().y, powerUp3->GetWidth(), powerUp3->GetHeight() }, Rectangle{ paddle->GetPos().x, paddle->GetPos().y, paddle->GetWidth(), paddle->GetHeight() }))
					{
						isPowerUp3Picked = true;
					}

				}

				if (isPowerUp1Picked)
				{
					powerUp1Timer += GetFrameTime();
				}
				if (isPowerUp2Picked && powerUp2Timer < 10)
				{
					powerUp2->Collect(paddle, ball);
					powerUp2Timer += GetFrameTime();
					for (int i = 0; i < bricksPerColumn; i++)
					{
						for (int j = 0; j < bricksPerRow; j++)
						{
							powerUp2->CheckShootAndBrickCollision(bricks[i][j], smashedBicksCount);
						}
					}
				}
				if (isPowerUp3Picked)
				{
					powerUp3->Collect(paddle, ball);
					powerUp3Timer += GetFrameTime();
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
				if (powerUp3Timer >= 10)
				{
					isPowerUp3Picked = false;
					powerUp3->SetIsActive(false);
					powerUp3Timer = 0;
				}

				for (int i = 0; i < bricksPerColumn; i++)
				{
					for (int j = 0; j < bricksPerRow; j++)
					{
						/*powerUp2->CheckShootAndBrickCollision(bricks[i][j], smashedBicksCount);*/
						if (bricks[i][j]->GetIsActive())
						{
							bricks[i][j]->Update(ball);
							if (CheckCollisionRecs(Rectangle{ ball->GetPos().x,ball->GetPos().y,ball->GetWidth(),ball->GetHeight() }, Rectangle{ bricks[i][j]->GetPos().x,bricks[i][j]->GetPos().y,bricks[i][j]->GetWidth(),bricks[i][j]->GetHeight() }))
							{

								do
								{
									powerUpRandom = GetRandomValue(1, 10);
								} while (powerUpRandom == lastPowerUpRandom);
								lastPowerUpRandom = powerUpRandom;

								if (powerUpRandom == 10)
								{
									powerUp1->SetIsActive(true);
									powerUp1->SetPos(bricks[i][j]->GetPos());

								}
								else if (powerUpRandom == 9)
								{
									powerUp2->SetIsActive(true);
									powerUp2->SetPos(bricks[i][j]->GetPos());
								}
								else if (powerUpRandom == 8)
								{
									powerUp3->SetIsActive(true);
									powerUp3->SetPos(bricks[i][j]->GetPos());
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
				resetLevel = true;
				currentScreen = GAMEOVER;

			}
			if (ball->GetPos().y >= GetScreenHeight())
			{
				lifes--;
				InitValues();
			}

			gameOver = GameOver();
			if (gameOver)
			{
				resetLevel = true;
			}
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
			if (powerUp3->GetIsActive())
			{
				if (!isPowerUp3Picked)
				{
					powerUp3->Draw();
				}
				else
				{
					powerUp3->DrawFloor();
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
			return lifes <= 0;
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