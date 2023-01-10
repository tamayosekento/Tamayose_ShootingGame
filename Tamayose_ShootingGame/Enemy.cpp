#include"DxLib.h"
#include "Enemy.h"
#include"StraightBullets.h"
#include"CircleBullet.h"

//#define _ENEMY_BULLET_ALL_ 100

struct MoveInfomation
{
	T_Location targetLocation;	//���W
	int pattern;				//�p�^�[��
	int next;					//next
	int waitTimeFlame;			//����
	int attackPattern;			//�A�^�b�N�p�^�[��
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

		//��ʊO�ɍs������e������
		if (bullets[bulletCount]->isScreenOut())
		{
			DeleteBullet(bulletCount);
			bulletCount--;
		}
	}

	if (bulletCount < 300/*30*/ && bullets[bulletCount] == nullptr)
	{
		//�e������낤
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
	//���W������Ă���
	T_Location nextLocation = GetLocation();

	//�������W�ɂ��邩�ǂ���
	if ((nextLocation.y == locations[current].y) &&
		(nextLocation.x == locations[current].x))
	{
		current = next[current];
	}

	//�ړI�n�ɂ��Ȃ������ꍇ
	else
	{
		//y���W�̖ړI�n���Ⴄ��
		if (nextLocation.y != locations[current].y)
		{
			//���̍��W���ړI�n���傫����
			if (nextLocation.y < locations[current].y)
			{
				//�ړI�n�Ɍ�����
				nextLocation.y += speed.y;

				//�ړI�n���щz������
				if ((GetLocation().y <= locations[current].y) &&
					(locations[current].y <= nextLocation.y))
				{
					//�ړI�n��ς���
					nextLocation.y = locations[current].y;
				}
			}
			//���̍��W���ړI�n����������
			else
			{
				//�V���ȖړI�n�Ɍ�����
				nextLocation.y -= speed.y;

				//�ړI�n���щz������
				if ((nextLocation.y <= locations[current].y) &&
					(locations[current].y <= GetLocation().y))
				{
					//�ړI�n��ς���
					nextLocation.y = locations[current].y;
				}
			}
		}

		//x���W�̖ړI�n���Ⴄ��
		if (nextLocation.x != locations[current].x)
		{
			//���̍��W���ړI�n���傫����
			if (nextLocation.x < locations[current].x)
			{
				//�ړI�n�Ɍ�����
				nextLocation.x += speed.x;

				//�ړI�n���щz������
				if ((GetLocation().x <= locations[current].x) &&
					(locations[current].x <= nextLocation.x))
				{
					//�ړI�n��ς���
					nextLocation.x = locations[current].x;
				}
			}
			//���̍��W���ړI�n����������
			else
			{
				//�ړI�n�Ɍ�����
				nextLocation.x -= speed.x;

				//�ړI�n���щz������
				if ((nextLocation.x <= locations[current].x) &&
					(locations[current].x <= GetLocation().x))
				{
					//�ړI�n��ς���
					nextLocation.x = locations[current].x;
				}
			}
		}
	}

	SetLocation(nextLocation);
}