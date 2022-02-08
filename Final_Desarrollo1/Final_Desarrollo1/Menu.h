#pragma once
#include"raylib.h"
namespace gamemanager
{
	namespace menu
	{
		void InitMenu();
		void UpdateMenu();
		void DrawMenu();
		void UnloadMenu();
		extern bool isMultiplayer;

	}
}