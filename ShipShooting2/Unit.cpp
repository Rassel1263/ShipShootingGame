#include "DXUT.h"
#include "Unit.h"

Unit::Unit()
{
    colorShader = new ColorShader();

    layer = 5;
}

void Unit::Update(float deltaTime)
{
    if (hit)
    {
        hitTimer += deltaTime;

        if (hitTimer >= hitTime)
        {
            hit = false;
            hitTimer = 0.0f;
        }
    }

    GetNowSprite().Update(deltaTime);
}

void Unit::Render()
{
    ri.pos = pos;

    if (hit)
        colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(1, 1, 1, 1));
    else
        GetNowSprite().Render(ri);

    Object::Render();
}

void Unit::OnCollision(Collider& coli)
{
 
}

bool Unit::Move(float deltaTime)
{
    return false;
}

void Unit::Hit(float damage)
{
    if (hit) return;

    hit = true;
    this->ability.hp -= damage;

    if (ability.hp <= 0) ability.hp = 0;
}

void Unit::SetAni(float rotate)
{
    int fixRotateScene = (int)((rotate / 15.0f)) % 24;

    if (pastScene != fixRotateScene)
    {
        ri.rotate = 0;
        pastScene = fixRotateScene;
    }

    renderNum = (abs(fixRotateScene));
}

Sprite& Unit::GetNowSprite()
{
    return sprites[renderNum];
}

