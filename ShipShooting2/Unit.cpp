#include "DXUT.h"
#include "Unit.h"

Unit::Unit()
{
}

void Unit::Update(float deltaTime)
{
    GetNowSprite().Update(deltaTime);
}

void Unit::Render()
{
    ri.pos = pos;
    GetNowSprite().Render(ri);
}

bool Unit::Move(float deltaTime)
{
    return false;
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

