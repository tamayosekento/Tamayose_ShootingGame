#pragma once
#include "CharaBase.h"

//#define _ENEMY_BULLET_ALL_ 100

class Enemy : public CharaBase
{
private:
	int hp;
	int point;
	int shotNum;

public:
	Enemy(T_Location location);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Hit(int damage) override;
	bool HpCheck();
	int GetPoint();
	void Move();
};

