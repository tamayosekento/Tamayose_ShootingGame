#pragma once
#include "CharaBase.h"

class Player : public CharaBase
{
private:
	int score;
	int life;
	int player;

public:
	Player(T_Location location);

public:
	void Update() override;
	void Draw() override;
	void Hit(int damage) override;
	void Hit(class ItemBase* item);
	bool LifeCheck();
	int GetScore();
	void AddScore(int score);
};

