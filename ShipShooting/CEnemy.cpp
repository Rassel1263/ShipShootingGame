#include "Header.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/MarineUnit");
	this->pos = { 0, 200 };
}

void CEnemy::Update(float deltaTime)
{
	//pos.y -= nowScene->player->ability.speed / 2* deltaTime;

	spr.Update(deltaTime);
}

void CEnemy::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

bool CEnemy::Move(float deltaTime)
{
	return false;
}
