#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
    team = Team::Enemy;
    hitTime = 0.1f;
 
    this->pos = pos;
}

void CEnemy::Update(float deltaTime)
{
    Unit::Update(deltaTime);
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
