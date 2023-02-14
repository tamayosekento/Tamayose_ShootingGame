#include "GameOverScene.h"
#include"DxLib.h"
#include "KeyManager.h"
#include "TitleScene.h"

GameOverScene::GameOverScene()
{

}

void GameOverScene::Update()
{

}

void GameOverScene::Draw() const
{
	DrawString(540, 260, "GameOver", 0xffffff);
	DrawString(540, 360, "�`SPACE�L�[��������Title�ց`", 0xffffff);
}

AbstractScene* GameOverScene::ChangeScene()
{
	if (KeyManager::OnKeyPressed(KEY_INPUT_SPACE))
	{
		return dynamic_cast<AbstractScene*>(new (TitleScene));
	}

	return this;
}
