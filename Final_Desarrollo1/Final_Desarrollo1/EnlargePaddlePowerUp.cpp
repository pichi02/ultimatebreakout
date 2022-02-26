#include "EnlargePaddlePowerUp.h"

EnlargePaddlePowerUp::EnlargePaddlePowerUp(Vector2 pos, float speed, float width, float height, bool isActive) :PowerUp(pos, speed, width, height, isActive)
{
}

EnlargePaddlePowerUp::~EnlargePaddlePowerUp()
{
}

void EnlargePaddlePowerUp::Collect(Paddle* paddle, Ball* ball)
{
	paddle->SetWidth(300.0f);
}

void EnlargePaddlePowerUp::Draw()
{
	DrawRectangle(GetPos().x, GetPos().y, GetWidth(), GetHeight(), MAGENTA);
}

