#pragma once
#include"raylib.h"
#include"Ball.h"
class Brick
{
private:
	Vector2 pos;
	float width;
	float height;
	bool isActive;
public:
	Brick(float width, float height, Vector2 pos);
	~Brick();
	void CheckBallCollision(Ball* ball);
	void Draw();
	Vector2 GetPos();
	float GetWidth();
	float GetHeight();
	bool GetIsActive();
	void Update(Ball* ball);
	void SetIsActive(bool isActive);
};

