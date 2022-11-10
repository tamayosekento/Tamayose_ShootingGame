#pragma once
#include "SphereCollider.h"
#include"E_ITEM_TYPE.h"

class ItemBase : public SphereCollider
{
private:
	E_ITEM_TYPE type;

protected:
	T_Location speed;

public:
	ItemBase(T_Location location, float radius, E_ITEM_TYPE type, T_Location speed);

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	E_ITEM_TYPE GetType();
};

