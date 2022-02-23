#include "EnlargePaddlePowerUp.h"

EnlargePaddlePoweUp::EnlargePaddlePoweUp(Vector2 pos, float speed, float width, float height, bool isActive) :PowerUp(pos, speed, width, height, isActive)
{
}

EnlargePaddlePoweUp::~EnlargePaddlePoweUp()
{
}

void EnlargePaddlePoweUp::Collect(Paddle* paddle)
{
	paddle->SetWidth(300.0f);
}

