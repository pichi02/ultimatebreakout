#include "Paddle.h"

Paddle::Paddle(Vector2 pos, float speed, int width, int height)
{
	this->pos = pos;
	this->speed = speed;
	this->width = width;
	this->height = height;
}

Paddle::~Paddle()
{
}

void Paddle::Move()
{
	if (IsKeyDown('A'))
	{
		if (pos.x >= 0)
		{
			pos.x -= speed * GetFrameTime();
		}

	}
	else if (IsKeyDown('D'))
	{
		if (pos.x < GetScreenWidth() - width)
		{
			pos.x += speed * GetFrameTime();
		}

	}

}

Vector2 Paddle::GetPos()
{
	return pos;
}

float Paddle::GetSpeed()
{
	return speed;
}

float Paddle::GetWidth()
{
	return width;
}

float Paddle::GetHeight()
{
	return height;
}

void Paddle::Update()
{
	Move();
}

void Paddle::Draw()
{
	DrawRectangle(pos.x, pos.y, width, height, BLUE);
}

void Paddle::SetWidth(float width)
{
	this->width = width;
}


