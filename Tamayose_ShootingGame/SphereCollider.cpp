#include "SphereCollider.h"
#include"math.h"

//コンストラクタ
SphereCollider::SphereCollider (T_Location location, float radius)
{
	this->location.x = location.x;
	this->location.y = location.y;
	this->radius = radius;
}

//SphereCollider型同士の当たり判定
bool SphereCollider::HitSphere(const SphereCollider* collider) const
{
	//自分から相手へのベクトルを計算する
	//計算で出したベクトルの大きさと
	//自分と相手の半径より
	//ベクトルの大きさが小さければ、当たっている

	//自分と相手との間のベクトルを計算
	float vectorX = fabsf(this->location.x - collider->GetLocation().x);
	float vectorY = fabsf(this->location.y - collider->GetLocation().y);

	//ベクトルの大きさを計算
	float vectorLength = (vectorX * vectorX) + (vectorY * vectorY);
	vectorLength = sqrtf(vectorLength);

	//自分と相手の半径の合計値を計算
	float sumRadius = radius + collider->GetRadius();

	//当たり判定の結果を格納
	bool ret = (vectorLength < sumRadius);

	return ret;
}

//中心座標の取得
T_Location SphereCollider::GetLocation() const
{
	return location;
}

//中心座標の設定
void SphereCollider:: SetLocation(T_Location location)
{
	this->location.x = location.x;
	this->location.y = location.y;
}

//半径の取得
float SphereCollider::GetRadius() const
{
	return radius;
}