#include "GameClearScene.h"
#include <DxLib.h>
#include "KeyManager.h"
#include "TitleScene.h"

GameClearScene::GameClearScene()
{

}

void GameClearScene::Update()
{

}

void GameClearScene::Draw() const
{
	DrawString(540, 260, "GameClear", 0xffffff);
    DrawString(540, 360, "�`SPACE�L�[��������Title�ց`", 0xffffff);
}

AbstractScene* GameClearScene::ChangeScene()
{
	if (KeyManager::OnKeyPressed(KEY_INPUT_SPACE))
	{
		return dynamic_cast<AbstractScene*>(new (TitleScene));
	}

    return this;
}
