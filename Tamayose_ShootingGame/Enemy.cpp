#include"DxLib.h"
#include "Enemy.h"

Enemy::Enemy(T_Location location)
	:CharaBase(location, 20.f, T_Location{ 0,0.5 }), hp(10), point(10)
{

}

void Enemy::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.y += 0.5;
	SetLocation(newLocation);
}

void Enemy::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));
}

void Enemy::Hit()
{

}

bool Enemy::HpCheck()
{
	bool ret = (hp <= 0);
	return ret;
}

int Enemy::GetPoint()
{
	return point;
}
