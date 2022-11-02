#include "CharaBase.h"

CharaBase::CharaBase(T_Location location, float radius, T_Location speed)
	: SphereCollider(location, radius), speed(speed), image(nullptr), bullets(nullptr)
{

}

BulletsBase** CharaBase::GetBullets()
{
	return bullets;
}

void CharaBase::DeleteBullet(int bulletNum)
{
	delete bullets[bulletNum];
	bullets[bulletNum] = nullptr;

	//”z—ñ‚ð‘O‚É‹l‚ß‚é
	//for (int i = bulletCount; i < (30 - 1); i++)
	//{
	//	if (bullets[i + 1] == nullptr)
	//	{
	//		break;
	//	}
	//	bullets[i] = bullets[i + 1];
	//	bullets[i + 1] = nullptr;
	//}

	for (int i = bulletNum + 1; i < 30; i++)
	{
		if (bullets[i] == nullptr)
		{
			break;
		}
		bullets[i - 1] = bullets[i];
		bullets[i] = nullptr;
	}
}
