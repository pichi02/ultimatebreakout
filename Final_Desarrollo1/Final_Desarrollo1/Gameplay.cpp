#include "Gameplay.h"
#include"GameManager.h"


using namespace gamemanager;
namespace gamemanager
{

	namespace gameplay
	{
		extern bool gameOver = false;
		bool collide = false;
		Rectangle paddle;
		Rectangle ball;
		float paddleSpeed;
		const int bricksPerColumn = 11;
		const int bricksPerRow = 5;
		Vector2 ballSpeed;
		Rectangle bricks[bricksPerColumn][bricksPerRow];
		bool isBrickActive[bricksPerColumn][bricksPerRow];
		

		void InitValues()
		{
			paddleSpeed = 0.2f;
			paddle.x = GetScreenWidth() / 2;
			paddle.y = GetScreenHeight() * 0.9;
			paddle.width = 150;
			paddle.height = 10;
			ballSpeed.x = 0.2f;
			ballSpeed.y = -0.2f;
			ball.x = paddle.x;
			ball.y = GetScreenHeight() * 0.7;
			ball.width = 10;
			ball.height = 10;
			InitBricks();
			
		}
		void UpdateFrame()
		{
			if (!gameOver)
			{
				UpdatePaddle();
				UpdateBall();
				CheckBallAndPaddleCollision();
				BricksAndBallCollision();
			}
			else
			{
				currentScreen = MENU;

			}
			gameOver = GameOver();
		}
		void Draw()
		{
			ClearBackground(BLACK);
			DrawPaddle();
			DrawBall();
			DrawBricks();
		}
		void ResetValues()
		{
		}
		void UnloadGameplay()
		{
		}
		void DrawPaddle()
		{
			DrawRectangle(paddle.x, paddle.y, paddle.width, paddle.height, BLUE);
		}
		void UpdatePaddle()
		{
			if (IsKeyDown('A'))
			{
				if (paddle.x >= 0)
				{
					paddle.x -= paddleSpeed;
				}

			}
			else if (IsKeyDown('D'))
			{
				if (paddle.x < GetScreenWidth() - paddle.width)
				{
					paddle.x += paddleSpeed;
				}

			}
			paddle.x = ball.x - paddle.width / 2;

		}
		void UpdateBall()
		{
			ball.x += ballSpeed.x;
			ball.y += ballSpeed.y;

			if (ball.x <= 0 || ball.x >= GetScreenWidth() - ball.width)
			{
				ballSpeed.x *= -1;
			}
			if (ball.y <= 0)
			{
				ballSpeed.y *= -1;
			}

		}
		void DrawBall()
		{
			DrawRectangle(ball.x, ball.y, ball.width, ball.height, WHITE);
		}

		void CheckBallAndPaddleCollision()
		{

			if (CheckCollisionRecs(ball, paddle) && !collide)
			{
				collide = true;
				if (ball.x > paddle.x + paddle.width / 2 && ballSpeed.x < 0)
				{
					ballSpeed.x *= -1;
				}
				if (ball.x < paddle.x + paddle.width / 2 && ballSpeed.x>0)
				{
					ballSpeed.x *= -1;
				}

				ballSpeed.y *= -1;
			}
			else if (!CheckCollisionRecs(ball, paddle))
			{
				collide = false;
			}
		}

		bool GameOver()
		{
			return ball.y >= GetScreenHeight();;
		}

		void InitBricks()
		{

			for (int i = 0; i < bricksPerColumn; i++)
			{
				for (int j = 0; j < bricksPerRow; j++)
				{
					bricks[i][j].width = 60;
					bricks[i][j].height = 30;
					bricks[i][j].x = (bricks[i][j].width * 1.2) * i;
					bricks[i][j].y = (bricks[i][j].height * 1.2) * j;
					isBrickActive[i][j] = true;
				}
			}
		}

		void DrawBricks()
		{
			for (int i = 0; i < bricksPerColumn; i++)
			{
				for (int j = 0; j < bricksPerRow; j++)
				{
					if (isBrickActive[i][j])
					{
						DrawRectangle(bricks[i][j].x, bricks[i][j].y, bricks[i][j].width, bricks[i][j].height, ORANGE);
					}

				}
			}
		}

		void BricksAndBallCollision()
		{
			Vector2 ballPosition = { ball.x + ball.width / 2, ball.y + ball.height / 2 };

			for (int i = 0; i < bricksPerColumn; i++)
			{
				for (int j = 0; j < bricksPerRow; j++)
				{
					if (isBrickActive[i][j])
					{
						if (CheckCollisionRecs(bricks[i][j], ball))
						{
							Vector2 oppositeCorner = { bricks[i][j].x + bricks[i][j].width,bricks[i][j].y + bricks[i][j].height };
							isBrickActive[i][j] = false;
							if (ballPosition.x < bricks[i][j].x)
							{
								if (ballSpeed.x > 0)
								{
									ballSpeed.x *= -1;
								}

							}
							else if (ballPosition.x > oppositeCorner.x)
							{
								if (ballSpeed.x < 0)
								{
									ballSpeed.x *= -1;
								}
							}

							if (ballPosition.y < bricks[i][j].y)
							{
								if (ballSpeed.y > 0)
								{
									ballSpeed.y *= -1;
								}
							}
							else if (ballPosition.y > oppositeCorner.y)
							{
								if (ballSpeed.y < 0)
								{
									ballSpeed.y *= -1;
								}
							}

						}
					}

				}
			}
		}


	}
}