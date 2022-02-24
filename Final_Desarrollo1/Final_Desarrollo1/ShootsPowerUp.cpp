#include "ShootsPowerUp.h"

ShootsPowerUp::ShootsPowerUp(Vector2 pos, float speed, float width, float height, bool isActive, Paddle* paddle) :PowerUp(pos, speed, width, height, isActive)
{
	for (int i = 0; i < shootsAmount; i++)
	{
		shoots[i] = new Shoot({ paddle->GetPos().x + paddle->GetWidth() / 2 ,paddle->GetPos().y }, 5, 10, 750.0f);
	}
	shootRate = 0;
}

ShootsPowerUp::~ShootsPowerUp()
{
}

void ShootsPowerUp::Collect(Paddle* paddle)
{

	shootRate += 5;

	for (int i = 0; i < shootsAmount; i++)
	{
		if (!shoots[i]->GetIsActive() && shootRate % 2500 == 0)
		{
			shoots[i]->SetPosition({ paddle->GetPos().x + paddle->GetWidth() / 2,paddle->GetPos().y });

			shoots[i]->SetIsActive(true);
			break;
		}
	}

	for (int i = 0; i < shootsAmount; i++)
	{
		if (shoots[i]->GetIsActive())
		{
			shoots[i]->Move(paddle);
			shoots[i]->Draw();
			if (shoots[i]->GetPos().y < 0)
			{
				shoots[i]->SetIsActive(false);
				shootRate = 0;
			}
		}

	}
}
void ShootsPowerUp::CheckShootAndBrickCollision(Brick* brick, int& smashedBricksCount)
{
	for (int i = 0; i < shootsAmount; i++)
	{
		if (CheckCollisionRecs(Rectangle{ shoots[i]->GetPos().x,shoots[i]->GetPos().y,shoots[i]->GetWidth(),shoots[i]->GetHeight() }, Rectangle{ brick->GetPos().x,brick->GetPos().y,brick->GetWidth(),brick->GetHeight() }))
		{
			if (brick->GetIsActive())
			{
				shoots[i]->SetIsActive(false);
				brick->SetIsActive(false);
				smashedBricksCount++;
			}
			
		}
	}

}

void ShootsPowerUp::Draw()
{
	DrawRectangle(GetPos().x, GetPos().y, GetWidth(), GetHeight(), BLUE);
}

void ShootsPowerUp::TurnOffShoots()
{
	for (int i = 0; i < shootsAmount; i++)
	{
		shoots[i]->SetIsActive(false);
	}
}


