#pragma once
#include "AbstractScene.h"

class GameClearScene : public AbstractScene
{
private:

public:
	GameClearScene();

	//デストラクタ
	virtual ~GameClearScene() {};

	//描画以外の更新を実装する
	virtual void Update() override;

	//描画に関することを実装する
	virtual void Draw() const override;

	//シーンの変更処理
	virtual AbstractScene* ChangeScene() override;
};

