#pragma once
#include "AbstractScene.h"
#include"Player.h"
#include"Enemy.h"
#include"ItemBase.h"

class GameMainScene : public AbstractScene
{
private:
	Player* player;
	Enemy** enemy;
	ItemBase** items;

public:
	GameMainScene();

	//デストラクタ
	virtual ~GameMainScene() {};

	//描画以外の更新を実装する
	virtual void Update() override;

	//描画に関することを実装する
	virtual void Draw() const override;

	//シーンの変更処理
	virtual AbstractScene* ChangeScene() override;
};

