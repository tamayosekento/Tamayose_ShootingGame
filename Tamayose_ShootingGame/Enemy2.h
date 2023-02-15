#pragma once
#include "CharaBase.h"

struct T_MoveInfomation
{
	int pattern;				//�s���p�^�[��
	T_Location destination;		//�ړI�n
	int nextArrayNum;			//���̔z��ԍ�
	int waitFlameTime;			//�҂�����
	int attackType;				//�U���̎��
};

class Enemy2 : public CharaBase
{
private:
	int hp;
	int point;
	int shotNum;
	int enemy;

	T_MoveInfomation moveInfo[5] = {};

	int current = 0;
	int waitTime = 0;

public:
	Enemy2(T_Location location);

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Hit(int damage) override;
	bool HpCheck();
	int GetPoint();
	void Move();
	void inputCSV();
};

