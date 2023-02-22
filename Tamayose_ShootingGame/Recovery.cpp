#include "Recovery.h"
#include"DxLib.h"

Recovery::Recovery(T_Location location)
	:ItemBase(location, 30.f, E_ITEM_TYPE::Heal, T_Location{ 0,0.5 }), volume(2)
{
	item = LoadGraph("images/Item.png");
}

void Recovery::Update()
{
	T_Location newLocation = GetLocation();
	newLocation.y += speed.y;
	SetLocation(newLocation);
}

void Recovery::Draw()
{
	DrawRotaGraph(GetLocation().x, GetLocation().y, 1, 0, item, TRUE);
}

int Recovery::GetVolume()
{
	return volume;
}
