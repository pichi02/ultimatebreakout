#pragma once
#include"PowerUp.h"
class EnlargePaddlePoweUp :public PowerUp
{
private:

public:
	EnlargePaddlePoweUp(Vector2 pos, float speed, float width, float height, bool isActive);
	~EnlargePaddlePoweUp();
	void Collect(Paddle* paddle);

};
