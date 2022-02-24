#pragma once
#include"PowerUp.h"
class EnlargePaddlePowerUp :public PowerUp
{
private:

public:
	EnlargePaddlePowerUp(Vector2 pos, float speed, float width, float height, bool isActive);
	~EnlargePaddlePowerUp();
	void Collect(Paddle* paddle);
	void Draw();

};
