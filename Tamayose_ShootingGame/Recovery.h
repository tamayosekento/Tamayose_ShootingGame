#pragma once
#include "ItemBase.h"

class Recovery : public ItemBase
{
private:
	int volume;

public:
	virtual void Update() override;
	virtual void Draw() override;
	int GetVolume();
};	