#include "CircleBullet.h"
#include <DxLib.h>

#define _USE_MATH_DEFINES
#include<math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

CircleBullet::CircleBullet(T_Location location, float speed, int degAngle)
	:BulletsBase(location, 5.f, 1, T_Location{ 0,0 })
{
	enemyBullet = LoadGraph("images/EnemyBullet.png");
	int deg = degAngle % 360;
	double rad = (M_PI / 180) * deg;
	float x = (abs(deg) == 90 || deg == 270) ? 0 : cos(rad);
	float y = sin(rad);

	this->speed = T_Location{ (speed * x),(speed * y) };
}

void CircleBullet::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	newLocation.x += speed.x;
	SetLocation(newLocation);
}

void CircleBullet::Draw()
{
	DrawRotaGraph(GetLocation().x, GetLocation().y, 1, 0, enemyBullet, TRUE);
}

bool CircleBullet::isScreenOut()
{
	bool ret = ((GetLocation().y + GetRadius()) <= 0);
	if (ret)
	{
		return ret;
	}

	ret = (SCREEN_HEIGHT <= (GetLocation().y - GetRadius()));
	if (ret)
	{
		return ret;
	}

	ret = ((GetLocation().x + GetRadius()) <= 0);
	if (ret)
	{
		return ret;
	}

	ret = (SCREEN_WIDTH <= (GetLocation().x - GetRadius()));
	return ret;
}
