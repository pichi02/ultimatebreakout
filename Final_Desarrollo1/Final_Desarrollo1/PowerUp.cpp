#include "PowerUp.h"

PowerUp::PowerUp(Vector2 pos, float speed, float width, float height, bool isActive)
{
	this->pos = pos;
	this->speed = speed;
	this->width = width;
	this->height = height;
	this->isActive = isActive;
}

PowerUp::~PowerUp()
{
}

Vector2 PowerUp::GetPos()
{
	return pos;
}

float PowerUp::GetSpeed()
{
	return speed;
}

float PowerUp::GetWidth()
{
	return width;
}

float PowerUp::GetHeight()
{
	return height;
}

void PowerUp::SetPos(Vector2 pos)
{
	this->pos = pos;
}

void PowerUp::SetIsActive(bool isActive)
{
	this->isActive = isActive;
}

void PowerUp::Move()
{
	pos.y += speed;
}

bool PowerUp::GetIsActive()
{
	return isActive;
}

void PowerUp::Draw()
{
	DrawRectangle(pos.x, pos.y, width, height, MAGENTA);
}
