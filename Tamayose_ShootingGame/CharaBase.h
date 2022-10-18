#pragma once
#include "SphereCollider.h"

class CharaBase : public SphereCollider
{
private:
    //bullets(ポインタ配列)
    T_Location speed;

protected:
    int* image;

public:
    CharaBase(T_Location location, float radius, T_Location speed);

public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Hit() = 0;
    //GetBullets()

};

