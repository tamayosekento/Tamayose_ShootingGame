#pragma once
#include "ItemBase.h"

class Recovery : public ItemBase
{
private:
	int volume;

public:
	Recovery(T_Location location);

public:
	virtual void Update() override;
	virtual void Draw() override;
	int GetVolume();
};	