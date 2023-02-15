#include"DxLib.h"
#include "StraightBullets.h"

StraightBullets::StraightBullets(T_Location location, T_Location speed)
	:BulletsBase(location, 5.f, 1, speed)
{
	playerBullet = LoadGraph("images/Bullet.png");
}

void StraightBullets::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void StraightBullets::Draw()
{
	DrawRotaGraph(GetLocation().x, GetLocation().y, 0.03, 0, playerBullet, TRUE);
}

bool StraightBullets::isScreenOut()
{
	bool ret = ((GetLocation().y + GetRadius()) <= 0);
	if (ret)
	{
		return ret;
	}

	ret = (720 <= (GetLocation().y - GetRadius()));
	return ret;
}
