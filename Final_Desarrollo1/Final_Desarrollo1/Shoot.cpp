#include "Shoot.h"

Shoot::Shoot(Vector2 pos, float width, float height, float speed)
{
	this->pos = pos;
	this->width = width;
	this->height = height;
	this->speed = speed;
	isActive = false;
}

Shoot::~Shoot()
{
}

void Shoot::SetIsActive(bool isActive)
{
	this->isActive = isActive;
}

void Shoot::SetPosition(Vector2 pos)
{
	this->pos = pos;
}

void Shoot::Move(Paddle* paddle)
{
	pos.y -= speed*GetFrameTime();
}

Vector2 Shoot::GetPos()
{
	return pos;
}

float Shoot::GetWidth()
{
	return width;
}

float Shoot::GetHeight()
{
	return height;
}

float Shoot::GetSpeed()
{
	return speed;
}

bool Shoot::GetIsActive()
{
	return isActive;
}

void Shoot::Draw()
{
	DrawRectangle(pos.x, pos.y, width, height, WHITE);
}


