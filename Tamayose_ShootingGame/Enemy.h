//#pragma once
//#include "CharaBase.h"
//
////#define _ENEMY_BULLET_ALL_ 100
//
//struct T_MoveInfomation
//{
//	int pattern;				//行動パターン
//	T_Location destination;		//目的地
//	int nextArrayNum;			//次の配列番号
//	int waitFlameTime;			//待ち時間
//	int attackType;				//攻撃の種類
//};
//
//class Enemy : public CharaBase
//{
//private:
//	int hp;
//	int point;
//	int shotNum;
//	int enemy;
//
//	T_MoveInfomation moveInfo[5] = {};
//
//	int current = 0;
//	int waitTime = 0;
//
//public:
//	Enemy(T_Location location);
//
//public:
//	virtual void Update() override;
//	virtual void Draw() override;
//	virtual void Hit(int damage) override;
//	bool HpCheck();
//	int GetPoint();
//	void Move();
//	void inputCSV();
//};
//
