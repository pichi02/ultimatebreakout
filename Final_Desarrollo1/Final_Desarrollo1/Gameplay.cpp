#include "Gameplay.h"

namespace gamemanager
{

	namespace gameplay
	{
		extern bool gameOver = false;
		bool collide = false;
		Rectangle paddle;
		Rectangle ball;
		float paddleSpeed;
		Vector2 ballSpeed;


		void InitValues()
		{
			paddleSpeed = 0.2f;
			paddle.x = GetScreenWidth() / 2;
			paddle.y = GetScreenHeight() * 0.9;
			paddle.width = 150;
			paddle.height = 10;
			ballSpeed.x = 0.1f;
			ballSpeed.y = -0.1f;
			ball.x = paddle.x;
			ball.y = GetScreenHeight() * 0.7;
			ball.width = 10;
			ball.height = 10;

		}
		void UpdateFrame()
		{
			UpdatePaddle();
			UpdateBall();
			CheckBallAndPaddleCollision();
		}
		void Draw()
		{
			ClearBackground(BLACK);
			DrawPaddle();
			DrawBall();
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
				if (ball.x<paddle.x+paddle.width/2 && ballSpeed.x>0)
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

	}
}