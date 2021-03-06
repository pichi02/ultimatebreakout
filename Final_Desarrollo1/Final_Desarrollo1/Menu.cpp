#include "Menu.h"
#include "raylib.h"
#include"GameManager.h"


using namespace gamemanager;

namespace gamemanager
{

	namespace menu
	{
		static char text1[] = "JUGAR";
		static char text3[] = "CREDITOS";
		static char text4[] = "SALIR";
		static char text5[] = "V 1.0";
		static char gameTitle[] = "ULTIMATE BREAKOUT";
		static int sizeText2 = 0;
		static int sizeText3 = 0;
		static int text1PositionX = 0;
		static int text1PositionY = 0;
		static int text3PositionX = 0;
		static int text3PositionY = 0;
		static int text4PositionX = 0;
		static int text4PositionY = 0;
		static int text5PositionX = 0;
		static int text5PositionY = 0;
		static int titlePosX = 0;
		static int titlePosY = 0;
		static int titleTextSize = 0;

		static Vector2 mousePoint;
		static Rectangle rect2;
		static Rectangle rect3;
		static Rectangle rect4;
		static Color colorRect1;
		static Color colorRect2;
		static Color colorRect3;
		static Color colorRect4;

		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;
		static const int scaleAux3 = 1280;

		static int halfScreenWidth = 0;
		static int halfScreenHeight = 0;



		Texture2D menuBackgroundTexture;
		Image menuImage;
		Rectangle frameRecMenuBackground;
		Vector2 menuBackgroundPosition;

		Music menuMusic;

		extern bool isMultiplayer = false;

		void InitMenu()
		{

			/*menuImage = LoadImage("res/menuTexture.png");*/
			
			halfScreenWidth = GetScreenWidth() / 2;
			halfScreenHeight = GetScreenHeight() / 2;

			menuBackgroundTexture.height = GetScreenHeight();
			menuBackgroundTexture.width = GetScreenWidth();
			frameRecMenuBackground = { 0.0f, 0.0f, (float)menuBackgroundTexture.width, (float)menuBackgroundTexture.height };
			menuBackgroundPosition = { 0,0 };
			menuImage = LoadImage("res/background.png");
			menuBackgroundTexture = LoadTextureFromImage(menuImage);
			menuMusic = LoadMusicStream("res/menuMusic.ogg");
			sizeText2 = (GetScreenWidth() * 20) / scaleAux1;
			sizeText3 = (GetScreenWidth() * 15) / scaleAux1;
			titleTextSize = (GetScreenWidth() * 50) / scaleAux1;
			text1PositionX = halfScreenWidth - MeasureText(text1, sizeText2) / 2;
			text1PositionY = halfScreenHeight + GetScreenHeight() * 0.0333333;
			text3PositionX = halfScreenWidth - MeasureText(text3, sizeText2) / 2;
			text3PositionY = halfScreenHeight + GetScreenHeight() * 0.1333333;
			text4PositionX = halfScreenWidth - MeasureText(text4, sizeText2) / 2;
			text4PositionY = halfScreenHeight + GetScreenHeight() * 0.2333333;
			text5PositionX = GetScreenWidth() * 0.05;
			text5PositionY = GetScreenHeight() * 0.95;
			titlePosX = halfScreenWidth - MeasureText(gameTitle, titleTextSize) / 2;
			titlePosY = GetScreenHeight() / 100 * 20;

			colorRect1 = BLUE;
			colorRect2 = BLUE;
			colorRect3 = BLUE;
			colorRect4 = BLUE;


			rect2.height = (GetScreenWidth() * 80) / scaleAux2;
			rect2.width = (GetScreenWidth() * 290) / scaleAux2;
			rect2.x = halfScreenWidth - rect2.width / 2;
			rect2.y = halfScreenHeight + GetScreenHeight() * 0.11;

			rect3.height = (GetScreenWidth() * 80) / scaleAux2;
			rect3.width = (GetScreenWidth() * 290) / scaleAux2;
			rect3.x = halfScreenWidth - rect2.width / 2;
			rect3.y = halfScreenHeight + GetScreenHeight() * 0.21;

			rect4.height = (GetScreenWidth() * 80) / scaleAux2;
			rect4.width = (GetScreenWidth() * 290) / scaleAux2;
			rect4.x = halfScreenWidth - rect2.width / 2;
			rect4.y = halfScreenHeight + GetScreenHeight() * 0.01;

		
		}

		void UpdateMenu()
		{
			PlayMusicStream(menuMusic);
			UpdateMusicStream(menuMusic);
			mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, rect2))
			{
				colorRect2.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					UnloadMenu();
					
					currentScreen = CREDITS;
				}
			}
			else colorRect2.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect3))
			{
				colorRect3.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					exit = true;
				}
			}
			else colorRect3.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect4))
			{
				colorRect4.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					InitValues();
					UnloadMenu();
					currentScreen = GAMEPLAY;
				}
			}
			else colorRect4.a = 255;
		}

		void DrawMenu()
		{
			ClearBackground(WHITE);
			DrawTextureEx(menuBackgroundTexture, { 0,0 }, 0, (GetScreenWidth() * 1.0f) / GetScreenWidth(), WHITE);
			DrawRectangleRec(rect2, colorRect2);
			DrawRectangleRec(rect3, colorRect3);
			DrawRectangleRec(rect4, colorRect4);
			DrawText(text1, text1PositionX, text1PositionY, sizeText2, BLACK);
			DrawText(text3, text3PositionX, text3PositionY, sizeText2, BLACK);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, BLACK);
			DrawText(text5, text5PositionX, text5PositionY, sizeText2, WHITE);
			DrawText(gameTitle, titlePosX, titlePosY, titleTextSize, WHITE);
		}

		void UnloadMenu()
		{
			

		}

	}
}