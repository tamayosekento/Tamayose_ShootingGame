#include"DxLib.h"
#include "Enemy.h"
#include"StraightBullets.h"
#include"CircleBullet.h"

//#define _ENEMY_BULLET_ALL_ 100

//T_Location locations[3] =
//{
//	{   640, 150},
//	{1200.4, 150},
//	{  80.2, 150},
//};

//int next[3] = 
//{
//	1,
//	2,
//	1
//};

void Enemy::inputCSV(const char* pass)
{
	FILE* fp;			//FILE型構造体
	errno_t error;		//fopen_sのエラー確認

	error = fopen_s(&fp, pass, "r");
	if (error != 0)
	{
		//エラー発生
		return;
	}
	else
	{
		//ファイルを開いた
		char line[100];
		for (int i = 0; fgets(line, 100, fp) != NULL; i++)
		//while(fgets(line, 100, fp) != NULL)
		{
			sscanf_s(line, "%d, %f, %f, %d, %d, %d",
					&moveInfo[i].pattern,
					&moveInfo[i].destination.x,
					&moveInfo[i].destination.y,
					&moveInfo[i].nextArrayNum,
					&moveInfo[i].waitFlameTime,
					&moveInfo[i].attackType);
		}
		return;
	}

	fclose(fp);			//ファイルを閉じる
}

Enemy::Enemy(T_Location location, const char* pass)
	:CharaBase(location, 60.f, T_Location{ 3,3 }), hp(10), point(10), shotNum(0)
{
	enemy = LoadGraph("images/Enemy.png");

	inputCSV(pass);
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

	switch (moveInfo[current].pattern)
	{
	case 0:
		Move();
		break;

	case 1:
		waitTime++;
		if (moveInfo[current].waitFlameTime <= waitTime)
		{
			waitTime = 0;
			current = moveInfo[current].nextArrayNum;
		}
		break;

	default:
		break;
	}
	

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

	if (moveInfo[current].attackType != 0)
	{
		if (bulletCount < 300/*30*/ && bullets[bulletCount] == nullptr)
		{
			if (moveInfo[current].attackType == 1)
			{
				bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0,5 });
			}
			else if (moveInfo[current].attackType == 2)
			{
				shotNum++;
				bullets[bulletCount] = new CircleBullet(GetLocation(), 5.f, (37 * shotNum));
			}
			else if (moveInfo[current].attackType == 3)
			{
				shotNum++;
				bullets[bulletCount] = new CircleBullet(GetLocation(), 5.f, (45 * shotNum));
			}

			////弾幕を作ろう
			//bullets[bulletCount] =
			//	new CircleBullet(GetLocation(), 2.f, (23 * shotNum));
			//shotNum++;
			////bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0,2 });
		}
	}
}

void Enemy::Draw()
{
	DrawRotaGraph(GetLocation().x,GetLocation().y,1,0,enemy,TRUE);

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
	if ((nextLocation.y == moveInfo[current].destination.y) &&
		(nextLocation.x == moveInfo[current].destination.x))
	{
		current = moveInfo[current].nextArrayNum;
	}

	//目的地にいなかった場合
	else
	{
		//y座標の目的地が違う時
		if (nextLocation.y != moveInfo[current].destination.y)
		{
			//今の座標より目的地が大きい時
			if (nextLocation.y < moveInfo[current].destination.y)
			{
				//目的地に向かう
				nextLocation.y += speed.y;

				//目的地を飛び越えた時
				if ((GetLocation().y <= moveInfo[current].destination.y) &&
					(moveInfo[current].destination.y <= nextLocation.y))
				{
					//目的地を変える
					nextLocation.y = moveInfo[current].destination.y;
				}
			}
			//今の座標より目的地が小さい時
			else
			{
				//新たな目的地に向かう
				nextLocation.y -= speed.y;

				//目的地を飛び越えた時
				if ((nextLocation.y <= moveInfo[current].destination.y) &&
					(moveInfo[current].destination.y <= GetLocation().y))
				{
					//目的地を変える
					nextLocation.y = moveInfo[current].destination.y;
				}
			}
		}

		//x座標の目的地が違う時
		if (nextLocation.x != moveInfo[current].destination.x)
		{
			//今の座標より目的地が大きい時
			if (nextLocation.x < moveInfo[current].destination.x)
			{
				//目的地に向かう
				nextLocation.x += speed.x;

				//目的地を飛び越えた時
				if ((GetLocation().x <= moveInfo[current].destination.x) &&
					(moveInfo[current].destination.x <= nextLocation.x))
				{
					//目的地を変える
					nextLocation.x = moveInfo[current].destination.x;
				}
			}
			//今の座標より目的地が小さい時
			else
			{
				//目的地に向かう
				nextLocation.x -= speed.x;

				//目的地を飛び越えた時
				if ((nextLocation.x <= moveInfo[current].destination.x) &&
					(moveInfo[current].destination.x <= GetLocation().x))
				{
					//目的地を変える
					nextLocation.x = moveInfo[current].destination.x;
				}
			}
		}
	}

	SetLocation(nextLocation);
}