#pragma once
#include "AbstractScene.h"
#include"Player.h"
#include"Enemy.h"
#include"ItemBase.h"
#include "Enemy2.h"

class GameMainScene : public AbstractScene
{
private:
	Player* player;
	Enemy** enemy;
	Enemy2** enemy2;
	ItemBase** items;

public:
	GameMainScene();

	//�f�X�g���N�^
	virtual ~GameMainScene() {};

	//�`��ȊO�̍X�V����������
	virtual void Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const override;

	//�V�[���̕ύX����
	virtual AbstractScene* ChangeScene() override;
};

