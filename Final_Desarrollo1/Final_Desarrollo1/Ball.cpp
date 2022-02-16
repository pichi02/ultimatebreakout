#include "Ball.h"

Ball::Ball(Vector2 pos, Vector2 speed, float width, float height)
{
	this->pos = pos;
	this->speed = speed;
	this->width = width;
	this->height = height;
	isActive = false;
}

Ball::~Ball()
{
}

Vector2 Ball::GetPosition()
{
	return pos;
}

Vector2 Ball::GetSpeed()
{
	return speed;
}

float Ball::GetWidth()
{
	return width;
}

float Ball::GetHeight()
{
	return height;
}

void Ball::Move(Paddle *paddle)
{
	if (isActive)
	{
		pos.x += speed.x * GetFrameTime();
		pos.y += speed.y * GetFrameTime();
	}
	else
	{
		pos.x = paddle->GetPos().x + paddle->GetWidth() / 2;
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		isActive = true;
	}
	
}

void Ball::CheckWallCollision()
{

	if (pos.x <= 0 || pos.x >= GetScreenWidth() - width)
	{
		speed.x *= -1;
	}
	if (pos.y <= 0)
	{
		speed.y *= -1;
	}

}

void Ball::CheckPaddleCollision(Paddle paddle, bool& collide)
{

	if (CheckCollisionRecs(Rectangle{ pos.x,pos.y,width,height }, Rectangle{ paddle.GetPos().x,paddle.GetPos().y, paddle.GetWidth(),paddle.GetHeight() }) && !collide)
	{
		collide = true;
		if (pos.x > paddle.GetPos().x + paddle.GetWidth() / 2 && speed.x < 0)
		{
			speed.x *= -1;
		}
		if (pos.x < paddle.GetPos().x + paddle.GetWidth() / 2 && speed.x>0)
		{
			speed.x *= -1;
		}

		speed.y *= -1;
	}
	else if (!CheckCollisionRecs(Rectangle{ pos.x,pos.y,width,height }, Rectangle{ paddle.GetPos().x,paddle.GetPos().y, paddle.GetWidth(),paddle.GetHeight() }))
	{
		collide = false;
	}
}

void Ball::Draw()
{
	DrawRectangle(pos.x, pos.y, width, height, WHITE);
}

void Ball::Update(Paddle* paddle, bool& collide)
{
	Move(paddle);
	CheckWallCollision();
	CheckPaddleCollision(*paddle, collide);
}

void Ball::ReverseXSpeed()
{
	speed.x *= -1;
}

void Ball::ReverseYSpeed()
{
	speed.y *= -1;
}

bool Ball::GetIsActive()
{
	return isActive;
}

void Ball::SetIsActive(bool isActive)
{
	this->isActive = isActive;
}
