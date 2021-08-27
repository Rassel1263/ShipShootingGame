#pragma once

class Object;
class Collider
{
public:
	enum class TYPE
	{
		AABB,
	} type;

	struct AABB
	{
		D3DXVECTOR2 min = { 0, 0 }, max = { 0.0f, 0.0f };
	} aabb;

	Collider(const std::wstring& name, Object* obj, AABB* aabb);
	Object* obj;
	std::wstring name;
};


bool IntersectCollider(Collider& col1, Collider& col2);
bool IntersectAABBAABB(D3DXVECTOR2 min1, D3DXVECTOR2 max1, D3DXVECTOR2 min2, D3DXVECTOR2 max2);