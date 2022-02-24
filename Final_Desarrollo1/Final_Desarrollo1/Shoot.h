#pragma once
#include"raylib.h"
#include"Paddle.h"

class Shoot
{
private:
	Vector2 pos;
	float width;
	float height;
	float speed;
	bool isActive;
public:
	Shoot(Vector2 pos, float width, float height, float speed);
	~Shoot();
	void SetIsActive(bool isActive);
	void SetPosition(Vector2 pos);
	void Move(Paddle* paddle);
	Vector2 GetPos();
	float GetWidth();
	float GetHeight();
	float GetSpeed();
	bool GetIsActive();
	void Draw();
	
};

