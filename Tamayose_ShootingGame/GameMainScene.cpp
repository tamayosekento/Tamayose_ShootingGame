#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
	T_Location location = T_Location{ 20,100 };
	player = new Player(location);

	enemy = new Enemy * [10];
	for (int i = 0; i < 10; i++)
	{
		enemy[i] = nullptr;
	}
	enemy[0] = new Enemy(T_Location{ 200, 0 });
}

//描画以外の更新を実装する
void GameMainScene::Update()
{
	player->Update();
	
	int enemyCount;
	for (enemyCount = 0; enemyCount < 10; enemyCount++)
	{
		if (enemy[enemyCount] == nullptr)
		{
			break;
		}
		enemy[enemyCount]->Update();
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
}

//シーンの変更処理
AbstractScene* GameMainScene::ChangeScene()
{
	return this;
}