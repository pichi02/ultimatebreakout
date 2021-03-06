#pragma once
#include"raylib.h"
#include"Paddle.h"
#include"Ball.h"
class PowerUp
{
private:
	Vector2 pos;
	float speed;
	float width;
	float height;
	bool isActive;
public:
	PowerUp(Vector2 pos, float speed, float width, float heigth, bool isActive);
	virtual void Collect(Paddle* paddle, Ball* ball) = 0;
	~PowerUp();
	Vector2 GetPos();
	float GetSpeed();
	float GetWidth();
	float GetHeight();
	void SetPos(Vector2 pos);
	void SetIsActive(bool isActive);
	void Move();
	bool GetIsActive();
	virtual void Draw() = 0;


};

