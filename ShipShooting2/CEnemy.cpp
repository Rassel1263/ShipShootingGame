#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
    team = Team::Enemy;
 
    this->pos = pos;
}

void CEnemy::Update(float deltaTime)
{
    GetNowSprite().Update(deltaTime);
}

void CEnemy::Render()
{
    Unit::Render();
}

void CEnemy::OnCollision(Collider& coli)
{
}

bool CEnemy::Move(float deltaTime)
{
    return false;
}
