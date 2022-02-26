#pragma once
#include"PowerUp.h"
class FloorPowerUp :public PowerUp
{
private:
	Rectangle floor;
public:
	FloorPowerUp(Vector2 pos, float speed, float width, float height, bool isActive, Rectangle floor);
	~FloorPowerUp();
	void Collect(Paddle* paddle, Ball* ball);
	void Draw();
	void DrawFloor();
	Rectangle GetFloor();


};

