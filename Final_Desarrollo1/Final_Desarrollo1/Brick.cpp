#include "Brick.h"

Brick::Brick(float width, float height, Vector2 pos)
{
	this->pos = pos;
	this->width = width;
	this->height = height;
	isActive = true;
}

Brick::~Brick()
{
}

void Brick::CheckBallCollision(Ball* ball)
{
	Vector2 ballPosition = { ball->GetPos().x + ball->GetWidth() / 2, ball->GetPos().y + ball->GetHeight() / 2 };
	if (isActive)
	{
		if (CheckCollisionRecs(Rectangle{ ball->GetPos().x,ball->GetPos().y,ball->GetWidth(),ball->GetHeight() }, Rectangle{ pos.x,pos.y,width,height }))
		{
			Vector2 oppositeCorner = { pos.x + width, pos.y + height };
			isActive = false;
			if (ballPosition.x < pos.x)
			{
				if (ball->GetSpeed().x > 0)
				{
					ball->ReverseXSpeed();
				}

			}
			else if (ballPosition.x > oppositeCorner.x)
			{
				if (ball->GetSpeed().x < 0)
				{
					ball->ReverseXSpeed();
				}
			}

			if (ballPosition.y < pos.y)
			{
				if (ball->GetSpeed().y > 0)
				{
					ball->ReverseYSpeed();
				}
			}
			else if (ballPosition.y > oppositeCorner.y)
			{
				if (ball->GetSpeed().y < 0)
				{
					ball->ReverseYSpeed();
				}
			}
		}
	}
}

void Brick::Draw()
{
	DrawRectangle(pos.x, pos.y, width, height, ORANGE);
}

Vector2 Brick::GetPos()
{
	return pos;
}

float Brick::GetWidth()
{
	return width;
}

float Brick::GetHeight()
{
	return height;
}

bool Brick::GetIsActive()
{
	return isActive;
}

void Brick::Update(Ball* ball)
{
	CheckBallCollision(ball);
}

void Brick::SetIsActive(bool isActive)
{
	this->isActive = isActive;
}
