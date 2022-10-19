#include "CharaBase.h"

CharaBase::CharaBase(T_Location location, float radius, T_Location speed)
	: SphereCollider(location, radius), speed(speed), image(nullptr), bullets(nullptr)
{

}

BulletsBase** CharaBase::GetBullets()
{
	return bullets;
}
