#include"DxLib.h"
#include "TitleScene.h"
#include"KeyManager.h"
#include"GameMainScene.h"

TitleScene::TitleScene()
{

}

//描画以外の更新を実装する
void TitleScene::Update()
{

}

//描画に関することを実装する
void TitleScene::Draw() const
{
	DrawString(540, 360, "～Enterキーを押してSTART～", 0xffffff);
}

//シーンの変更処理
AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnKeyPressed(KEY_INPUT_RETURN))
	{
		return dynamic_cast<AbstractScene*>(new (GameMainScene));
	}

	return this;
}
