#include "Pause.h"

#include <raylib.h>

//#include "Gameplay.h"
#include "Menu.h"
#include "GameManager.h"

using namespace gamemanager;
//using namespace gameplay;
using namespace menu;

namespace gamemanager
{
	namespace pause
	{
		bool mute = false;
		static char text1[] = "PAUSA";
		static char text2[] = "MENU";
		static char text3[] = "REINICIAR";
		static char text5[] = "SEGUIR";
		static int sizeText1 = 0;
		static int sizeText2 = 0;
		static int sizeText3 = 0;
		static int textPositionX = 0;
		static int textPositionY = 0;
		static int text2PositionX = 0;
		static int text2PositionY = 0;
		static int text3PositionX = 0;
		static int text3PositionY = 0;
		static int text5PositionX = 0;
		static int text5PositionY = 0;
		static Vector2 mousePoint;
		static Rectangle rect1;
		static Rectangle rect3;
		static Rectangle rect4;
		static Color colorRect1;
		static Color colorRect2;
		static Color colorRect3;
		static Color colorRect4;
		static Color backGround;

		Texture2D pauseBackgroundTexture;
		Image pauseImage;
		Rectangle pauseRecMenuBackground;
		Vector2 pauseBackgroundPosition;

		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;
	
		void InitPause()
		{
			sizeText1 = (GetScreenWidth() * 80) / scaleAux1;
			sizeText2 = (GetScreenWidth() * 20) / scaleAux1;
			sizeText3 = (GetScreenWidth() * 15) / scaleAux1;
			textPositionX = GetScreenWidth() / 2 - MeasureText(text1, sizeText1) / 2;
			textPositionY = GetScreenHeight() * 0.1333333;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText2) / 2;
			text2PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.1333333;
			text3PositionX = GetScreenWidth() / 2 - MeasureText(text3, sizeText2) / 2;
			text3PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.2333333;
			text5PositionX = GetScreenWidth() / 2 - MeasureText(text5, sizeText2) / 2;
			text5PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.0333333;

			colorRect1 = BLUE;
			colorRect2 = BLUE;
			colorRect3 = BLUE;
			colorRect4 = BLUE;
			backGround = BLANK;


			rect1.height = (GetScreenWidth() * 80) / scaleAux2;
			rect1.width = (GetScreenWidth() * 255) / scaleAux2;
			rect1.x = GetScreenWidth() / 2 - rect1.width / 2;
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.11;

		
			rect3.height = (GetScreenWidth() * 80) / scaleAux2;
			rect3.width = (GetScreenWidth() * 255) / scaleAux2;
			rect3.x = GetScreenWidth() / 2 - rect1.width / 2;
			rect3.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.21;

			rect4.height = (GetScreenWidth() * 80) / scaleAux2;
			rect4.width = (GetScreenWidth() * 255) / scaleAux2;
			rect4.x = GetScreenWidth() / 2 - rect1.width / 2;
			rect4.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.01;

			pauseBackgroundTexture.height = GetScreenHeight();
			pauseBackgroundTexture.width = GetScreenWidth();
			pauseRecMenuBackground = { 0.0f, 0.0f, (float)pauseBackgroundTexture.width, (float)pauseBackgroundTexture.height };
			pauseBackgroundPosition = { 0,0 };
			pauseImage = LoadImage("res/background.png");
			pauseBackgroundTexture = LoadTextureFromImage(pauseImage);
		}

		void UpdatePause()
		{
			mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, rect4))
			{
				colorRect4.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = GAMEPLAY;
			}
			else colorRect4.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect3))
			{
				colorRect3.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					resetLevel = true;
					currentScreen = GAMEPLAY;
					ResetValues();
				}
			}
			else colorRect3.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					
					currentScreen = MENU;
					/*UnloadGameplay();*/
					InitMenu();
					resetLevel = true;
					/*ResetValues();*/

				}
			}
			else colorRect1.a = 255;
			
		}

		void DrawPause()
		{
			ClearBackground(backGround);
			DrawTextureEx(pauseBackgroundTexture, { 0,0 }, 0, (GetScreenWidth() * 1.0f) / GetScreenWidth(), WHITE);
			DrawRectangleRec(rect1, colorRect1);
			DrawRectangleRec(rect3, colorRect3);
			DrawRectangleRec(rect4, colorRect4);
			DrawText(text1, textPositionX, textPositionY, sizeText1, RAYWHITE);
			DrawText(text2, text2PositionX, text2PositionY, sizeText2, BLACK);
			DrawText(text3, text3PositionX, text3PositionY, sizeText2, BLACK);
		
			DrawText(text5, text5PositionX, text5PositionY, sizeText2, BLACK);
		}
	}
}