#pragma once
#include"PowerUp.h"
#include"Brick.h"
#include"Shoot.h"
class ShootsPowerUp :public PowerUp
{
private:
	static const int shootsAmount = 10;
	Shoot* shoots[shootsAmount];
	int shootRate;
public:
	ShootsPowerUp(Vector2 pos, float speed, float width, float height, bool isActive, Paddle* paddle);
	~ShootsPowerUp();
	void Collect(Paddle* paddle, Ball* ball);
	void CheckShootAndBrickCollision(Brick* brick, int& smashedBricksCount);
	void Draw();

	void TurnOffShoots();


};

