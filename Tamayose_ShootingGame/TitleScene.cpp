#include"DxLib.h"
#include "TitleScene.h"
#include"KeyManager.h"
#include"GameMainScene.h"

TitleScene::TitleScene()
{

}

//�`��ȊO�̍X�V����������
void TitleScene::Update()
{

}

//�`��Ɋւ��邱�Ƃ���������
void TitleScene::Draw() const
{
	DrawString(540, 360, "�`Enter�L�[��������START�`", 0xffffff);
}

//�V�[���̕ύX����
AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnKeyPressed(KEY_INPUT_RETURN))
	{
		return dynamic_cast<AbstractScene*>(new (GameMainScene));
	}

	return this;
}
