#include "Gameplay.h"

namespace gamemanager
{

	namespace gameplay
	{
		extern bool gameOver = false;
		Rectangle paddle;
		float paddleSpeed = 0.2f;


		void InitValues()
		{
			paddle.x = GetScreenWidth() / 2;
			paddle.y = GetScreenHeight() * 0.9;
			paddle.width = 60;
			paddle.height = 10;

		}
		void UpdateFrame()
		{
			UpdatePaddle();
		}
		void Draw()
		{
			ClearBackground(BLACK);
			DrawPaddle();
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
	}
}