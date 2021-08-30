#include "Header.h"
#include "Collider.h"

Collider::Collider(const std::wstring& name, Object* obj, AABB* aabb, D3DXCOLOR color)
{
    if (aabb)
    {
        type = TYPE::AABB;
        this->aabb = *aabb;
    }

    this->tag = name;
    this->obj = obj;
    this->color = color;
    this->obj->bCollider = true;
}

bool IntersectCollider(Collider& col1, Collider& col2)
{
    if (col1.type == Collider::TYPE::AABB && col2.type == Collider::TYPE::AABB)
    {
        return IntersectAABBAABB(col1.obj->pos + col1.aabb.min, col1.obj->pos + col1.aabb.max, col2.obj->pos + col2.aabb.min, col2.obj->pos + col2.aabb.max);
    }

    return false;
}

bool IntersectAABBAABB(D3DXVECTOR2 min1, D3DXVECTOR2 max1, D3DXVECTOR2 min2, D3DXVECTOR2 max2)
{
    return min1.x < max2.x && max1.x > min2.x && min1.y < max2.y && max1.y > min2.y;
}
