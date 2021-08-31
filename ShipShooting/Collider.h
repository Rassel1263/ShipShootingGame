#pragma once

class Object;
class Collider
{
public:
	enum class TYPE
	{
		AABB,
		Circle
	} type;

	struct AABB
	{
		D3DXVECTOR2 min = { 0, 0 }, max = { 0.0f, 0.0f };
	} aabb;

	struct Circle
	{
		float radius = 0.0f;
	} circle;

	Collider(const std::wstring& name, Object* obj, AABB* aabb, Circle* circle = NULL, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));
	Object* obj;
	std::wstring tag;

	D3DXCOLOR color = D3DCOLOR_ARGB(255, 0, 0, 0);
};

D3DXVECTOR2 D3DXVec2Rotation(const D3DXVECTOR2& vec1, const float& rotate);
bool IntersectCollider(Collider& col1, Collider& col2);
bool IntersectAABBAABB(D3DXVECTOR2 min1, D3DXVECTOR2 max1, D3DXVECTOR2 min2, D3DXVECTOR2 max2);
bool IntersectCircleCircle(const D3DXVECTOR2& _p1, const float& _r1, const D3DXVECTOR2& _p2, const float& _r2);
