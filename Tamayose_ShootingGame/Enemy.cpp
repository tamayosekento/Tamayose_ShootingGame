#include"DxLib.h"
#include "Enemy.h"
#include"StraightBullets.h"
#include"CircleBullet.h"

//#define _ENEMY_BULLET_ALL_ 100

struct MoveInfomation
{
	T_Location targetLocation;	//座標
	int pattern;				//パターン
	int next;					//next
	int waitTimeFlame;			//時間
	int attackPattern;			//アタックパターン
};

MoveInfomation moveInfo[10] =
{
	{   640, 150, 0, 1,   0, 0},
	{1200.4, 150, 0, 2,   0, 0},
	{     0,   0, 1, 3, 180, 1},
	{  80.2, 150, 0, 4,   0, 2},
	{     0,   0, 1, 5, 180, 1},
	{1200.4, 150, 0, 2,   0, 1},
};

T_Location locations[3] =
{
	{   640, 150},
	{1200.4, 150},
	{  80.2, 150},
};

int next[3] = 
{
	1,
	2,
	1
};

int current = 0;

Enemy::Enemy(T_Location location)
	:CharaBase(location, 20.f, T_Location{ 1.5,1.5 }), hp(10), point(10), shotNum(0)
{
	bullets = new BulletsBase * [/*30*/300];
	for (int i = 0; i < /*30*/300; i++)
	{
		bullets[i] = nullptr;
	}
}

void Enemy::Update()
{
	//T_Location newLocation = GetLocation();
	//newLocation.y += speed.y;
	//SetLocation(newLocation);

	Move();

	int bulletCount;
	for (bulletCount = 0; bulletCount < /*30*/300; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Update();

		//画面外に行ったら弾を消す
		if (bullets[bulletCount]->isScreenOut())
		{
			DeleteBullet(bulletCount);
			bulletCount--;
		}
	}

	if (bulletCount < 300/*30*/ && bullets[bulletCount] == nullptr)
	{
		//弾幕を作ろう
		bullets[bulletCount] =
			new CircleBullet(GetLocation(), 2.f, (23 * shotNum));
		shotNum++;
		//bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0,2 });
	}
}

void Enemy::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));

	for (int bulletCount = 0; bulletCount < /*30*/300; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

void Enemy::Hit(int damage)
{
	if (0 < damage)
	{
		hp -= damage;
		if (hp < 0)
		{
			hp = 0;
		}
	}
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

void Enemy::Move()
{
	//座標を取ってくる
	T_Location nextLocation = GetLocation();

	//同じ座標にいるかどうか
	if ((nextLocation.y == locations[current].y) &&
		(nextLocation.x == locations[current].x))
	{
		current = next[current];
	}

	//目的地にいなかった場合
	else
	{
		//y座標の目的地が違う時
		if (nextLocation.y != locations[current].y)
		{
			//今の座標より目的地が大きい時
			if (nextLocation.y < locations[current].y)
			{
				//目的地に向かう
				nextLocation.y += speed.y;

				//目的地を飛び越えた時
				if ((GetLocation().y <= locations[current].y) &&
					(locations[current].y <= nextLocation.y))
				{
					//目的地を変える
					nextLocation.y = locations[current].y;
				}
			}
			//今の座標より目的地が小さい時
			else
			{
				//新たな目的地に向かう
				nextLocation.y -= speed.y;

				//目的地を飛び越えた時
				if ((nextLocation.y <= locations[current].y) &&
					(locations[current].y <= GetLocation().y))
				{
					//目的地を変える
					nextLocation.y = locations[current].y;
				}
			}
		}

		//x座標の目的地が違う時
		if (nextLocation.x != locations[current].x)
		{
			//今の座標より目的地が大きい時
			if (nextLocation.x < locations[current].x)
			{
				//目的地に向かう
				nextLocation.x += speed.x;

				//目的地を飛び越えた時
				if ((GetLocation().x <= locations[current].x) &&
					(locations[current].x <= nextLocation.x))
				{
					//目的地を変える
					nextLocation.x = locations[current].x;
				}
			}
			//今の座標より目的地が小さい時
			else
			{
				//目的地に向かう
				nextLocation.x -= speed.x;

				//目的地を飛び越えた時
				if ((nextLocation.x <= locations[current].x) &&
					(locations[current].x <= GetLocation().x))
				{
					//目的地を変える
					nextLocation.x = locations[current].x;
				}
			}
		}
	}

	SetLocation(nextLocation);
}