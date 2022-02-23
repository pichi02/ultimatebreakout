#pragma once
#include"raylib.h"
#include"Paddle.h"
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
	virtual void Collect(Paddle* paddle) = 0;
	~PowerUp();
	Vector2 GetPos();
	float GetSpeed();
	float GetWidth();
	float GetHeight();
	void SetPos(Vector2 pos);
	void SetIsActive(bool isActive);
	void Move();
	bool GetIsActive();
	void Draw();


};

