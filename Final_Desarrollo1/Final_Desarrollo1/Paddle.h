#pragma once
#include"raylib.h"

class Paddle
{
private:
	Vector2 pos;
	float speed;
	float width;
	float height;

public:
	Paddle(Vector2 pos, float speed, int width, int height);
	~Paddle();
	void Move();
	Vector2 GetPos();
	float GetSpeed();
	float GetWidth();
	float GetHeight();
	void Update();
	void Draw();
	
};

