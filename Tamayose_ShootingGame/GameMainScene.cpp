#include "GameMainScene.h"
#include"Recovery.h"
#include"Enemy.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include"KeyManager.h"
#include"DxLib.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int enemyCount;

GameMainScene::GameMainScene()
{
	T_Location location = T_Location{ 20,100 };
	player = new Player(location);

	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}

	enemy[0] = new Enemy(T_Location{ 640,0 },"data/Shooting.csv");

	items = new ItemBase * [10];
	for (int i = 0; i < 10; i++)
	{
		items[i] = nullptr;
	}
}

//描画以外の更新を実装する
void GameMainScene::Update()
{
	player->Update();
	
	
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}

		enemy[enemyCount]->Update();
	}

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr)
		{
			break;
		}
		items[i]->Update();
	}

	BulletsBase** bullet = player->GetBullets();
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}

		for (int bulletCount = 0; bulletCount < 30; bulletCount++)
		{
			if (bullet[bulletCount] == nullptr)
			{
				break;
			}

			if (enemy[enemyCount]->HitSphere(bullet[bulletCount]))
			{
				//エネミーにプレイヤーの弾がヒットしている

				//エネミーにダメージを与える
				enemy[enemyCount]->Hit(bullet[bulletCount]->GetDamage());

				//弾を削除する
				player->DeleteBullet(bulletCount);
				bulletCount--;

				//エネミーのHPが0以下だったらエネミーを削除する
				if (enemy[enemyCount]->HpCheck())
				{
					for (int i = 0; i < 10; i++)
					{
						if (items[i] == nullptr)
						{
							items[i] = new Recovery(enemy[enemyCount]->GetLocation());
							break;
						}

					}

					//スコアの加算
					player->AddScore(enemy[enemyCount]->GetPoint());

					//エネミーの削除
					delete enemy[enemyCount];
					enemy[enemyCount] = nullptr;

					//配列を前に詰める
					for (int i = enemyCount + 1; i < 30; i++)
					{
						if (enemy[i] == nullptr)
						{
							break;
						}
						enemy[i - 1] = enemy[i];
						enemy[i] = nullptr;
					}

					enemyCount--;
					break;
				}
			}
		}
	}

	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}

		bullet = enemy[enemyCount]->GetBullets();

		for (int i = 0; i < /*30*/300; i++)
		{
			if (bullet[i] == nullptr)
			{
				break;
			}

			if (player->HitSphere(bullet[i]))
			{
				//プレイヤーにダメージを与える
				player->Hit(bullet[i]->GetDamage());

				//弾を削除する
				enemy[enemyCount]->DeleteBullet(i);
				i--;
			}

		}
	}

	for (int itemCount = 0; itemCount < 10; itemCount++)
	{
		if (items[itemCount] == nullptr)
		{
			break;
		}
		if (items[itemCount]->HitSphere(player) == true)
		{
			//回復処理
			player->Hit(items[itemCount]);

			delete items[itemCount];
			items[itemCount] = nullptr;

			//配列を前に詰める
			for (int i = itemCount + 1; i < 30; i++)
			{
				if (items[i] == nullptr)
				{
					break;
				}
				items[i - 1] = items[i];
				items[i] = nullptr;
			}
			itemCount--;
		}
	}

}

//描画に関することを実装する
void GameMainScene::Draw() const
{
	player->Draw();

	for (int enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}

		enemy[enemyCount]->Draw();
	}

	for (int i = 0; i < 10; i++)
	{
		if (items[i] == nullptr)
		{
			break;
		}
		items[i]->Draw();
	}

	if (enemy[0] == nullptr)
	{
		DrawString(640, 320, "SHIFTを押して次のステージへ", 0xffffff);
	}
}

//シーンの変更処理
AbstractScene* GameMainScene::ChangeScene()
{
	if (enemy[0] == nullptr)
	{
		if (KeyManager::OnKeyClicked(KEY_INPUT_LSHIFT))
		{
			if (stageCount == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					enemy[i] = nullptr;
				}

				enemy[0] = new Enemy(T_Location{ 640,0 }, "data/Shooting.csv");
				enemy[1] = new Enemy(T_Location{ 640,150 }, "data/Shooting.csv");

				stageCount++;
			}
			else
			{
				return dynamic_cast<AbstractScene*>(new (GameClearScene));
			}
		}
	}


	if (player->LifeCheck())
	{
		return dynamic_cast<AbstractScene*>(new (GameOverScene));
	}

	return this;
}