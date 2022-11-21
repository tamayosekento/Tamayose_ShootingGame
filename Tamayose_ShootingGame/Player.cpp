#include"DxLib.h"
#include "Player.h"
#include"StraightBullets.h"
#include"KeyManager.h"
#include"Recovery.h"

Player::Player(T_Location location)
	: CharaBase(location, 10.f, T_Location{2,2}),score(0),life(10)
{
	bullets = new BulletsBase * [30];
	for (int i = 0; i < 30; i++)
	{
		bullets[i] = nullptr;
	}
}

void Player::Update()
{
	T_Location newLocation = GetLocation();
	if (KeyManager::OnKeyPressed(KEY_INPUT_W))
	{
		newLocation.y -= speed.y;
	}
	
	if (KeyManager::OnKeyPressed(KEY_INPUT_A))
	{
		newLocation.x -= speed.x;
	}

	if (KeyManager::OnKeyPressed(KEY_INPUT_S))
	{
		newLocation.y += speed.y;
	}

	if (KeyManager::OnKeyPressed(KEY_INPUT_D))
	{
		newLocation.x += speed.x;
	}

	SetLocation(newLocation);

	int bulletCount;
	for (bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Update();

		//‰æ–ÊŠO‚És‚Á‚½‚ç’e‚ðÁ‚·
		if (bullets[bulletCount]->isScreenOut())
		{
			DeleteBullet(bulletCount);
			bulletCount--;
		}
	}

	if (KeyManager::OnMouseClicked(MOUSE_INPUT_LEFT))
	{
		if (bulletCount < 30 && bullets[bulletCount] == nullptr)
		{
			bullets[bulletCount] = new StraightBullets((GetLocation()), T_Location{ 0,-2 });
		}
	}
}

void Player::Draw()
{
#define _DEBUG_MODE_

#ifdef _DEBUG_MODE_
	DrawFormatString(10, 10, GetColor(255, 255, 255), "life = %d",life);
	DrawFormatString(10, 30, GetColor(255, 255, 255), "score = %d",score);
#endif


	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 0, 0));

	for (int bulletCount = 0; bulletCount < 30; bulletCount++)
	{
		if (bullets[bulletCount] == nullptr)
		{
			break;
		}
		bullets[bulletCount]->Draw();
	}
}

void Player::Hit(int damage)
{
	if (0 <= damage)
	{
		life -= damage;

		if (life <= 0)
		{
			life = 0;
		}
	}
}

void Player::Hit(ItemBase* item)
{
	switch (item->GetType())
	{
		case E_ITEM_TYPE::Heal:
		{
			Recovery* recovery = dynamic_cast<Recovery*>(item);
			life += recovery->GetVolume();
			break;
		}
	default:
		break;
	}
}

bool Player::LifeCheck()
{
	bool ret = (life <= 0);
	return ret;
}

int Player::GetScore()
{
	return score;
}

void Player::AddScore(int score)
{
	if (0 <= score)
	{
		this->score += score;
	}
	
}
