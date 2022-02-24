#pragma once
#include"raylib.h"
#include"Paddle.h"
class Ball
{
private:
	Vector2 pos;
	Vector2 speed;
	float width;
	float height;
	bool isActive;

public:
	Ball(Vector2 pos, Vector2 speed, float width, float height);
	~Ball();
	Vector2 GetPosition();
	Vector2 GetSpeed();
	float GetWidth();
	float GetHeight();
	void Move(Paddle *paddle);
	void CheckWallCollision();
	void CheckPaddleCollision(Paddle paddle, bool& collide);
	void Draw();
	void Update(Paddle *paddle, bool& collide);
	void ReverseXSpeed();
	void ReverseYSpeed();
	bool GetIsActive();
	void SetIsActive(bool isActive);
	void IncreaseSpeed();



};

