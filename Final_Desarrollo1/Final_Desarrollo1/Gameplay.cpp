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
		extern bool resetLevel = true;
		bool win;
		bool ballAndPaddleCollide = false;
		bool ballAndWallXCollide;
		bool ballAndWallYCollide;
		bool isPowerUp1Picked;
		bool isPowerUp2Picked;
		bool isPowerUp3Picked;
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
		const float controllerInstructionTime = 16;

		Ball* ball;
		Paddle* paddle;
		Brick* bricks[bricksPerColumn][bricksPerRow];
		EnlargePaddlePowerUp* powerUp1;
		ShootsPowerUp* powerUp2;
		FloorPowerUp* powerUp3;

		Texture2D gameplayBackgroundTexture;
		Image gameplayImage;
		Rectangle frameRecGameplayBackground;
		Vector2 gameplayBackgroundPosition;

		Texture2D paddleSpriteTexture;
		Image paddleSpriteImage;
		Rectangle frameRecPaddleImage;
		Vector2 paddleImagePosition;

		Texture2D bigPaddleSpriteTexture;
		Image bigPaddleSpriteImage;
		Rectangle frameRecBigPaddleImage;
		Vector2 bigPaddleImagePosition;

		Texture2D ballSpriteTexture;
		Image ballSpriteImage;
		Rectangle frameRecBallImage;
		Vector2 ballImagePosition;

		Texture2D heartTexture;
		Image heartImage;
		Rectangle frameRecHeart;
		Vector2 heartImagePosition;

		Texture2D brickTexture;
		Image brickImage;
		Rectangle frameRecBrick;
		Vector2 brickImagePosition;

		Texture2D brick2Texture;
		Image brick2Image;
		Rectangle frameRecBrick2;
		Vector2 brick2ImagePosition;

		Texture2D powerUp1Texture;
		Image powerUp1Image;
		Rectangle frameRecpowerUp1;
		Vector2 powerUp1ImagePosition;

		Texture2D powerUp2Texture;
		Image powerUp2Image;
		Rectangle frameRecpowerUp2;
		Vector2 powerUp2ImagePosition;

		Texture2D powerUp3Texture;
		Image powerUp3Image;
		Rectangle frameRecpowerUp3;
		Vector2 powerUp3ImagePosition;

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
			if (rand <= 5)
			{
				ballSpeedX = 150.0f;
			}
			else
			{
				ballSpeedX = -150.0f;
			}
			ball = new Ball({ GetScreenWidth() / 2.0f,GetScreenHeight() * 0.87f }, { ballSpeedX,-150.0f }, 15, 15);
			paddle = new Paddle({ GetScreenWidth() / 2.5f,GetScreenHeight() * 0.9f }, 300.0f, 140, 10);
			powerUp1 = new EnlargePaddlePowerUp({ 0,0 }, 150.0f, 20, 20, false);
			powerUp2 = new ShootsPowerUp({ 0,0 }, 150.0f, 20, 20, false, paddle);
			powerUp3 = new FloorPowerUp({ 0,0 }, 150.0f, 20, 20, false, Rectangle{ 0,GetScreenHeight() * 0.93f,(float)GetScreenWidth(),10.0f });

			resetLevel = false;

			gameplayBackgroundTexture.height = GetScreenHeight();
			gameplayBackgroundTexture.width = GetScreenWidth();
			frameRecGameplayBackground = { 0.0f, 0.0f, (float)gameplayBackgroundTexture.width, (float)gameplayBackgroundTexture.height };
			gameplayBackgroundPosition = { 0,0 };
			gameplayImage = LoadImage("res/background.png");
			gameplayBackgroundTexture = LoadTextureFromImage(gameplayImage);

			paddleSpriteTexture.height = paddle->GetHeight();
			paddleSpriteTexture.width = paddle->GetWidth();
			frameRecPaddleImage = { 0.0f, 0.0f, (float)paddleSpriteTexture.width, (float)paddleSpriteTexture.height };
			paddleImagePosition = paddle->GetPos();
			paddleSpriteImage = LoadImage("res/paddle.png");
			paddleSpriteTexture = LoadTextureFromImage(paddleSpriteImage);

			bigPaddleSpriteTexture.height = paddle->GetHeight();
			bigPaddleSpriteTexture.width = 300.0f;
			frameRecBigPaddleImage = { 0.0f, 0.0f, (float)bigPaddleSpriteTexture.width, (float)bigPaddleSpriteTexture.height };
			bigPaddleImagePosition = paddle->GetPos();
			bigPaddleSpriteImage = LoadImage("res/bigpaddle.png");
			bigPaddleSpriteTexture = LoadTextureFromImage(bigPaddleSpriteImage);

			ballSpriteTexture.height = ball->GetHeight();
			ballSpriteTexture.width = ball->GetWidth();
			frameRecBallImage = { 0.0f, 0.0f, (float)ballSpriteTexture.width, (float)ballSpriteTexture.height };
			ballImagePosition = ball->GetPos();
			ballSpriteImage = LoadImage("res/ball.png");
			ballSpriteTexture = LoadTextureFromImage(ballSpriteImage);

			heartTexture.height = 16;
			heartTexture.width = 16;
			frameRecHeart = { 0.0f, 0.0f, (float)heartTexture.width, (float)heartTexture.height };
			heartImagePosition = { GetScreenWidth() * 0.9f,GetScreenHeight() * 0.01f };
			heartImage = LoadImage("res/heart.png");
			heartTexture = LoadTextureFromImage(heartImage);

			brickTexture.height = brickHeight;
			brickTexture.width = brickWidth;
			frameRecBrick = { 0.0f, 0.0f, (float)brickTexture.width, (float)brickTexture.height };
			brickImagePosition = { 0,0 };
			brickImage = LoadImage("res/brick.png");
			brickTexture = LoadTextureFromImage(brickImage);

			brick2Texture.height = brickHeight;
			brick2Texture.width = brickWidth;
			frameRecBrick2 = { 0.0f, 0.0f, (float)brick2Texture.width, (float)brick2Texture.height };
			brick2ImagePosition = { 0,0 };
			brick2Image = LoadImage("res/brick2.png");
			brick2Texture = LoadTextureFromImage(brick2Image);

			powerUp1Texture.height = 20;
			powerUp1Texture.width = 20;
			frameRecpowerUp1 = { 0.0f, 0.0f, (float)powerUp1Texture.width, (float)powerUp1Texture.height };
			powerUp1ImagePosition = powerUp1->GetPos();
			powerUp1Image = LoadImage("res/powerup1.png");
			powerUp1Texture = LoadTextureFromImage(powerUp1Image);

			powerUp2Texture.height = 20;
			powerUp2Texture.width = 20;
			frameRecpowerUp2 = { 0.0f, 0.0f, (float)powerUp2Texture.width, (float)powerUp2Texture.height };
			powerUp2ImagePosition = powerUp2->GetPos();
			powerUp2Image = LoadImage("res/powerup2.png");
			powerUp2Texture = LoadTextureFromImage(powerUp2Image);

			powerUp3Texture.height = 20;
			powerUp3Texture.width = 20;
			frameRecpowerUp3 = { 0.0f, 0.0f, (float)powerUp3Texture.width, (float)powerUp3Texture.height };
			powerUp3ImagePosition = powerUp3->GetPos();
			powerUp3Image = LoadImage("res/powerup3.png");
			powerUp3Texture = LoadTextureFromImage(powerUp3Image);


		}
		void UpdateFrame()
		{
			ballImagePosition = ball->GetPos();
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
					paddle->SetWidth(140);
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
				if (!isPowerUp1Picked && powerUp1->GetPos().y > GetScreenHeight())
				{
					powerUp1->SetIsActive(false);
				}
				if (!isPowerUp2Picked && powerUp2->GetPos().y > GetScreenHeight())
				{
					powerUp2->SetIsActive(false);
				}
				if (!isPowerUp3Picked && powerUp3->GetPos().y > GetScreenHeight())
				{
					powerUp3->SetIsActive(false);
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
									if (!powerUp1->GetIsActive())
									{
										powerUp1->SetIsActive(true);
										powerUp1->SetPos(bricks[i][j]->GetPos());

									}


								}
								else if (powerUpRandom == 9)
								{
									if (!powerUp2->GetIsActive())
									{
										powerUp2->SetIsActive(true);
										powerUp2->SetPos(bricks[i][j]->GetPos());
									}

								}
								else if (powerUpRandom == 8)
								{
									if (!powerUp3->GetIsActive())
									{
										powerUp3->SetIsActive(true);
										powerUp3->SetPos(bricks[i][j]->GetPos());
									}

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
			/*DrawText("x"lifes, GetScreenWidth() * 0.01f, GetScreenHeight() * 0.95f, 15, GREEN)*/;

			DrawTextureEx(gameplayBackgroundTexture, { 0,0 }, 0, (GetScreenWidth() * 1.0f) / GetScreenWidth(), WHITE);
			DrawText(TextFormat("x % 01i", lifes), GetScreenWidth() * 0.95f, GetScreenHeight() * 0.02f, 15, WHITE);
			DrawTextureEx(heartTexture, { heartImagePosition }, 0, (GetScreenWidth() * 1.0f) / GetScreenWidth(), WHITE);

			DrawTextureEx(ballSpriteTexture, { ball->GetPos().x,ball->GetPos().y }, 0, (GetScreenWidth() * 1.0f) / GetScreenWidth(), WHITE);
			if (timer <= controllerInstructionTime && (int)timer % 2 == 0)
			{
				DrawText("Press A to move LEFT", GetScreenWidth() * 0.01f, GetScreenHeight() * 0.95f, 15, GREEN);
				DrawText("Press D to move RIGHT", GetScreenWidth() * 0.78f, GetScreenHeight() * 0.95f, 15, GREEN);
			}
			DrawText("Press P to PAUSE", GetScreenWidth() * 0.01f, GetScreenHeight() * 0.02f, 15, WHITE);
			if (isPowerUp1Picked)
			{
				DrawTextureEx(bigPaddleSpriteTexture, { paddle->GetPos().x,paddle->GetPos().y - 4.0f }, 0, (GetScreenWidth()) / GetScreenWidth(), WHITE);
			}
			else
			{
				DrawTextureEx(paddleSpriteTexture, { paddle->GetPos().x,paddle->GetPos().y - 4.0f }, 0, (GetScreenWidth()) / GetScreenWidth(), WHITE);
			}

			if (isPowerUp2Picked && powerUp2Timer < 10)
			{
				powerUp2->DrawShoots();
			}
			for (int i = 0; i < bricksPerColumn; i++)
			{
				for (int j = 0; j < bricksPerRow; j++)
				{
					if (bricks[i][j]->GetIsActive())
					{
						/*bricks[i][j]->Draw();*/
						if (j % 2 == 0)
						{
							DrawTextureEx(brickTexture, { bricks[i][j]->GetPos().x - 2.0f,bricks[i][j]->GetPos().y }, 0, (GetScreenWidth() * 1.0f) / GetScreenWidth(), WHITE);
						}
						else
						{
							DrawTextureEx(brick2Texture, { bricks[i][j]->GetPos().x - 2.0f,bricks[i][j]->GetPos().y }, 0, (GetScreenWidth() * 1.0f) / GetScreenWidth(), WHITE);
						}
					}

				}
			}
			if (powerUp1->GetIsActive() && !isPowerUp1Picked)
			{
				/*powerUp1->Draw();*/
				DrawTextureEx(powerUp1Texture, { powerUp1->GetPos().x - 2.0f,powerUp1->GetPos().y - 2.0f }, 0, (GetScreenWidth()) / GetScreenWidth(), WHITE);

			}
			if (powerUp2->GetIsActive() && !isPowerUp2Picked)
			{
				/*powerUp2->Draw();*/
				DrawTextureEx(powerUp2Texture, { powerUp2->GetPos().x - 2.0f,powerUp2->GetPos().y - 2.0f }, 0, (GetScreenWidth()) / GetScreenWidth(), WHITE);
			}
			if (powerUp3->GetIsActive())
			{
				if (!isPowerUp3Picked)
				{
					/*powerUp3->Draw();*/
					DrawTextureEx(powerUp3Texture, { powerUp3->GetPos().x,powerUp3->GetPos().y }, 0, (GetScreenWidth()) / GetScreenWidth(), WHITE);
				}
				else
				{
					powerUp3->DrawFloor();
				}

			}
			/*paddle->Draw();*/
			/*ball->Draw();*/
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