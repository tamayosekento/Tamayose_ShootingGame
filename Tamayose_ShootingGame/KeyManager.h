#pragma once

class KeyManager
{
private:
	static char oldKey[256];
	static char nowKey[256];

	static int oldMouse;
	static int nowMouse;

private:
	KeyManager() = default;

public:
	static void Update();
	static bool OnKeyClicked(int key);		//�������u��(�L�[�{�[�h)
	static bool OnKeyReleased(int key);		//�������u��(�L�[�{�[�h)
	static bool OnKeyPressed(int key);		//�����Ă����(�L�[�{�[�h)

	static bool OnMouseClicked(int key);		//�������u��(�}�E�X)
	static bool OnMouseReleased(int key);		//�������u��(�}�E�X)
	static bool OnMousePressed(int key);		//�����Ă����(�}�E�X)
};

