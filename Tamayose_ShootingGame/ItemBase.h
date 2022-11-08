#pragma once
#include "SphereCollider.h"
#include"E_ITEM_TYPE.h"

class ItemBase : public SphereCollider
{
private:
	E_ITEM_TYPE type;

protected:
	T_Location spped;

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	E_ITEM_TYPE GetType();
};

