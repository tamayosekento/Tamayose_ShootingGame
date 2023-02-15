#pragma once
#include"BulletsBase.h"

class CircleBullet : public BulletsBase
{
public:
	int enemyBullet;

	CircleBullet(T_Location location, float speed, int degAngle);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool isScreenOut() override;
};

