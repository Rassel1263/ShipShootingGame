#include "DXUT.h"
#include "Unit.h"

Unit::Unit()
{
    colorShader = new ColorShader();

    smoke.LoadAll(L"Assets/Sprites/effect/onsmoke", 0.05f);
    fire.LoadAll(L"Assets/Sprites/effect/onfire", 0.05f);

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


    fire.Update(deltaTime);
    smoke.Update(deltaTime);
    GetNowSprite().Update(deltaTime);
}

void Unit::Render()
{
    ri.pos = pos;

    if (hit)
        colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(1, 1, 1, 1));
    else
        GetNowSprite().Render(ri);

    HpEffectRender();
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

void Unit::SetAni(float rotate, bool bigPlane)
{
    int fixRotateScene = 0;
    if(!bigPlane)
        fixRotateScene = (int)((rotate / 15.0f)) % 24;
    else
        fixRotateScene = (int)((rotate / 45)) % 8;

    renderNum = (abs(fixRotateScene));
}

void Unit::HpEffectRender()
{
    if (ability.hp / ability.maxHp <= 0.6f)
        smoke.Render(RenderInfo{ pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.2) });

    if (ability.hp / ability.maxHp <= 0.4f)
        fire.Render(RenderInfo{ pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.2) });
        
}


Sprite& Unit::GetNowSprite()
{
    return sprites[renderNum];
}

