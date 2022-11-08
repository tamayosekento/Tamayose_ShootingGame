#include "Recovery.h"
#include"DxLib.h"

void Recovery::Update()
{

}

void Recovery::Draw()
{
	DrawCircle(GetLocation().x, GetLocation().y, GetRadius(), GetColor(255, 255, 255));
}

int Recovery::GetVolume()
{
	return volume;
}
