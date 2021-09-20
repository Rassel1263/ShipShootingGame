#include "DXUT.h"
#include "Collider.h"

Collider::Collider(Object* obj, const std::wstring& name, AABB* aabb, D3DXCOLOR color)
{
    if (aabb)
    {
        type = Type::AABB;
        this->aabb = *aabb;
    }

    this->tag = name;
    this->obj = obj;
    this->color = color;
    this->obj->bCollider = true;
}

bool IntersectCollider(Collider& coli, Collider& coli2)
{
    if (coli.type == Collider::Type::AABB && coli2.type == Collider::Type::AABB)
        return IntersectAABBAABB(coli.obj->pos + coli.aabb.min, coli.obj->pos + coli.aabb.max, coli2.obj->pos + coli2.aabb.min, coli2.obj->pos + coli2.aabb.max);

    return false;
}

bool IntersectAABBAABB(D3DXVECTOR2 min1, D3DXVECTOR2 max1, D3DXVECTOR2 min2, D3DXVECTOR2 max2)
{
    return min1.x < max2.x && min2.x < max1.x && min1.y < max2.y && min2.y < max1.y;
}

