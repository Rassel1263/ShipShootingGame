#include "Header.h"
#include "Collider.h"

Collider::Collider(const std::wstring& name, Object* obj, AABB* aabb, Circle* circle,D3DXCOLOR color)
{
    if (aabb)
    {
        type = TYPE::AABB;
        this->aabb = *aabb;
    }   
    else if (circle)
    {
        type = TYPE::Circle;
        this->circle = *circle;
    }

    this->tag = name;
    this->obj = obj;
    this->color = color;
    this->obj->bCollider = true;
}

D3DXVECTOR2 D3DXVec2Rotation(const D3DXVECTOR2& vec1, const float& rotate)
{
    if (vec1 == D3DXVECTOR2(0.0f, 0.0f))
        return D3DXVECTOR2(0.0f, 0.0f);

    float radian = D3DXToRadian(-rotate);
    float sin = sinf(radian);
    float cos = cosf(radian);
    return D3DXVECTOR2(cos * vec1.x - sin * vec1.y, sin * vec1.x + cos * vec1.y);
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

bool IntersectCircleCircle(const D3DXVECTOR2& _p1, const float& _r1, const D3DXVECTOR2& _p2, const float& _r2)
{
    D3DXVECTOR2 p = D3DXVECTOR2(_p2.x - _p1.x, _p2.y - _p1.y);
    return p.x * p.x + p.y * p.y < (_r1 + _r2)* (_r1 + _r2);
}
