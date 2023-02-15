#include"DxLib.h"
#include "Enemy2.h"
#include"StraightBullets.h"
#include"CircleBullet.h"

void Enemy2::inputCSV()
{
	FILE* fp;			//FILE�^�\����
	errno_t error;		//fopen_s�̃G���[�m�F

	error = fopen_s(&fp, "data/Shooting.csv", "r");
	if (error != 0)
	{
		//�G���[����
		return;
	}
	else
	{
		//�t�@�C�����J����
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

	fclose(fp);			//�t�@�C�������
}

Enemy2::Enemy2(T_Location location)
	:CharaBase(location, 60.f, T_Location{ 1.5,1.5 }), hp(10), point(10), shotNum(0)
{
	enemy = LoadGraph("images/Enemy.png");

	inputCSV();
	bullets = new BulletsBase * [/*30*/200];
	for (int i = 0; i < /*30*/200; i++)
	{
		bullets[i] = nullptr;
	}
}

void Enemy2::Update()
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
	for (bulletCount = 0; bulletCount < /*30*/200; bulletCount++)
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

	if (moveInfo[current].attackType != 0)
	{
		if (bulletCount < 200/*30*/ && bullets[bulletCount] == nullptr)
		{
			if (moveInfo[current].attackType == 1)
			{
				bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0,5 });
			}
			else if (moveInfo[current].attackType == 2)
			{
				shotNum++;
				bullets[bulletCount] = new CircleBullet(GetLocation(), 5.f, (30 * shotNum));
			}

			////�e������낤
			//bullets[bulletCount] =
			//	new CircleBullet(GetLocation(), 2.f, (23 * shotNum));
			//shotNum++;
			////bullets[bulletCount] = new StraightBullets(GetLocation(), T_Location{ 0,2 });
		}
	}
}

void Enemy2::Draw()
{
	//DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 255));

	DrawRotaGraph(GetLocation().x, GetLocation().y, 0.3, 0, enemy, TRUE);

	for (int bulletCount = 0; bulletCount < /*30*/200; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

void Enemy2::Hit(int damage)
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

bool Enemy2::HpCheck()
{
	bool ret = (hp <= 0);
	return ret;
}

int Enemy2::GetPoint()
{
	return point;
}

void Enemy2::Move()
{
	//���W������Ă���
	T_Location nextLocation = GetLocation();

	//�������W�ɂ��邩�ǂ���
	if ((nextLocation.y == moveInfo[current].destination.y) &&
		(nextLocation.x == moveInfo[current].destination.x))
	{
		current = moveInfo[current].nextArrayNum;
	}

	//�ړI�n�ɂ��Ȃ������ꍇ
	else
	{
		//y���W�̖ړI�n���Ⴄ��
		if (nextLocation.y != moveInfo[current].destination.y)
		{
			//���̍��W���ړI�n���傫����
			if (nextLocation.y < moveInfo[current].destination.y)
			{
				//�ړI�n�Ɍ�����
				nextLocation.y += speed.y;

				//�ړI�n���щz������
				if ((GetLocation().y <= moveInfo[current].destination.y) &&
					(moveInfo[current].destination.y <= nextLocation.y))
				{
					//�ړI�n��ς���
					nextLocation.y = moveInfo[current].destination.y;
				}
			}
			//���̍��W���ړI�n����������
			else
			{
				//�V���ȖړI�n�Ɍ�����
				nextLocation.y -= speed.y;

				//�ړI�n���щz������
				if ((nextLocation.y <= moveInfo[current].destination.y) &&
					(moveInfo[current].destination.y <= GetLocation().y))
				{
					//�ړI�n��ς���
					nextLocation.y = moveInfo[current].destination.y;
				}
			}
		}

		//x���W�̖ړI�n���Ⴄ��
		if (nextLocation.x != moveInfo[current].destination.x)
		{
			//���̍��W���ړI�n���傫����
			if (nextLocation.x < moveInfo[current].destination.x)
			{
				//�ړI�n�Ɍ�����
				nextLocation.x += speed.x;

				//�ړI�n���щz������
				if ((GetLocation().x <= moveInfo[current].destination.x) &&
					(moveInfo[current].destination.x <= nextLocation.x))
				{
					//�ړI�n��ς���
					nextLocation.x = moveInfo[current].destination.x;
				}
			}
			//���̍��W���ړI�n����������
			else
			{
				//�ړI�n�Ɍ�����
				nextLocation.x -= speed.x;

				//�ړI�n���щz������
				if ((nextLocation.x <= moveInfo[current].destination.x) &&
					(moveInfo[current].destination.x <= GetLocation().x))
				{
					//�ړI�n��ς���
					nextLocation.x = moveInfo[current].destination.x;
				}
			}
		}
	}

	SetLocation(nextLocation);
}