#pragma once
#include "AbstractScene.h"

class GameClearScene : public AbstractScene
{
private:

public:
	GameClearScene();

	//�f�X�g���N�^
	virtual ~GameClearScene() {};

	//�`��ȊO�̍X�V����������
	virtual void Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;

	//�V�[���̕ύX����
	virtual AbstractScene* ChangeScene() override;
};

