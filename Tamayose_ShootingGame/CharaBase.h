#pragma once
#include "SphereCollider.h"
#include"BulletsBase.h"

class CharaBase : public SphereCollider
{
private:
    T_Location speed;

protected:
    BulletsBase** bullets;
    int* image;

public:
    CharaBase(T_Location location, float radius, T_Location speed);

public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Hit() = 0;
    BulletsBase** GetBullets();

};

