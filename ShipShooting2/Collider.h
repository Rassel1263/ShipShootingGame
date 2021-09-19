#pragma once

class Object;
class Collider
{
public:
	enum class Type
	{
		AABB
	} type;

	struct AABB
	{
		D3DXVECTOR2 min = { 0, 0 }, max = { 0.0f, 0.0f };
	} aabb;

	Collider(Object* obj, const std::wstring& name, AABB* aabb, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));
	Object* obj = NULL;
	std::wstring tag;
	D3DXCOLOR color;
};

bool IntersectCollider(Collider& coli, Collider& coli2);
bool IntersectAABBAABB(D3DXVECTOR2 min1, D3DXVECTOR2 max1, D3DXVECTOR2 min2, D3DXVECTOR2 max2);

