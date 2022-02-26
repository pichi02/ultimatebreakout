#include "FloorPowerUp.h"

FloorPowerUp::FloorPowerUp(Vector2 pos, float speed, float width, float height, bool isActive, Rectangle floor) :PowerUp(pos, speed, width, height, isActive)
{
	this->floor = floor;
}

FloorPowerUp::~FloorPowerUp()
{
}

void FloorPowerUp::Collect(Paddle* paddle, Ball* ball)
{
	if (CheckCollisionRecs(Rectangle{ floor.x,floor.y,floor.width,floor.height }, Rectangle{ ball->GetPos().x,ball->GetPos().y,ball->GetWidth(),ball->GetHeight() }))
	{
		ball->ReverseYSpeed();
	}
}

void FloorPowerUp::Draw()
{
	DrawRectangle(GetPos().x, GetPos().y, GetWidth(), GetHeight(), BROWN);
}

void FloorPowerUp::DrawFloor()
{
	DrawRectangle(floor.x, floor.y, floor.width, floor.height, GREEN);
}

Rectangle FloorPowerUp::GetFloor()
{
	return floor;
}





