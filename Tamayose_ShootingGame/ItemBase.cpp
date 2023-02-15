#include "ItemBase.h"
#include"DxLib.h"

ItemBase::ItemBase(T_Location location, float radius, E_ITEM_TYPE type, T_Location speed)
	:SphereCollider(location, radius), type(type), speed(speed)
{
	
}

void ItemBase::Update()
{
	
}

void ItemBase::Draw()
{
	
}

E_ITEM_TYPE ItemBase::GetType()
{
	return type;
}
