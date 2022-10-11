#include "GameMainScene.h"

//描画以外の更新を実装する
void GameMainScene::Update()
{

}

//描画に関することを実装する
void GameMainScene::Draw() const
{

}

//シーンの変更処理
AbstractScene* GameMainScene::ChangeScene()
{
	return this;
}