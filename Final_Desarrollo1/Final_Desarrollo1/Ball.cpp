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

Vector2 Ball::GetPos()
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

void Ball::Move(Paddle* paddle)
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

	if (pos.x <= 0 || pos.x + width >= GetScreenWidth())
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
		if (pos.x + width >= paddle.GetPos().x && pos.x + width < paddle.GetPos().x + paddle.GetWidth() / 5)
		{
			speed.x = -speed.y;
		}
		else if (pos.x + width >= paddle.GetPos().x + paddle.GetWidth() / 5 && pos.x + width < paddle.GetPos().x + paddle.GetWidth() * (2.0f / 5.0f))
		{
			speed.x = -(speed.y * 0.5);
		}
		else if (pos.x + width >= paddle.GetPos().x + paddle.GetWidth() * (2 / 5) && pos.x + width < paddle.GetPos().x + paddle.GetWidth() * (3.0f / 5.0f))
		{
			speed.x = 0;
		}
		else if (pos.x + width >= paddle.GetPos().x + paddle.GetWidth() * (3 / 5) && pos.x + width < paddle.GetPos().x + paddle.GetWidth() * (4.0f / 5.0f))
		{
			speed.x = (speed.y * 0.5);
		}
		else
		{
			speed.x = speed.y;
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

void Ball::IncreaseSpeed()
{
	if (speed.x > 0 && speed.x < 492)
	{
		speed.x += 0.01f;
	}
	else if (speed.x < 0 && speed.x > -492)
	{
		speed.x -= 0.01f;
	}

	if (speed.y > 0 && speed.y < 492)
	{
		speed.y += 0.01f;
	}
	else if (speed.y < 0 && speed.y > -492)
	{
		speed.y -= 0.01f;
	}

}
