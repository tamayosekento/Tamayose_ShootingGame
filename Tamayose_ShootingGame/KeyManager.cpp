#include"DxLib.h"
#include "KeyManager.h"

char KeyManager::oldKey[256];
char KeyManager::nowKey[256];

int KeyManager::oldMouse;
int KeyManager::nowMouse;

void KeyManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldKey[i] = nowKey[i];
	}

	if (GetHitKeyStateAll(nowKey) == -1)
	{
		throw - 1;
	}

	oldMouse = nowMouse;
	nowMouse = GetMouseInput();
}

/**********************************
 ***　キーボード
 ***********************************/

bool KeyManager::OnKeyClicked(int key)
{
	bool ret = ((nowKey[key] == 1) && (oldKey[key] != 1));		//押した瞬間(キーボード)

	return ret;
}

bool KeyManager::OnKeyReleased(int key)
{
	bool ret = ((nowKey[key] != 1) && (oldKey[key] == 1));		//離した瞬間(キーボード）

	return ret;
}

bool KeyManager::OnKeyPressed(int key)
{
	bool ret = (nowKey[key] == 1);		//押している間(キーボード)

	return ret;
}

/**********************************
 ***　マウス
 ***********************************/

bool KeyManager::OnMouseClicked(int key)
{
	bool ret = ((nowMouse & key) && (~oldMouse & key));		//押した瞬間(マウス)

	return ret;
}

bool KeyManager::OnMouseReleased(int key)
{
	bool ret = ((~nowMouse & key) && (oldMouse & key));		//離した瞬間(マウス)

	return ret;
}

bool KeyManager::OnMousePressed(int key)
{
	bool ret = (nowMouse & key);		//押している間(マウス)

	return ret;
}