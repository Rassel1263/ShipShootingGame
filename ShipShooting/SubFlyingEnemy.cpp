#include "Header.h"
#include "SubFlyingEnemy.h"

SubFlyingEnemy::SubFlyingEnemy(D3DXVECTOR2 pos, float startAngle, float addAngle, float maxAngle, float speed) : FlyingEnemy(pos)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/Sub");
	angle = startAngle;
	this->addAngle = addAngle;
	this->maxAngle = maxAngle;
	SetAbility(20, speed);

}

void SubFlyingEnemy::Update(float deltaTime)
{
	angle += addAngle * deltaTime;

	pos += D3DXVECTOR2(cosf(D3DXToRadian(angle)), sinf(D3DXToRadian(angle))) * ability.speed * deltaTime;

	CEnemy::Update(deltaTime);
}

void SubFlyingEnemy::Render()
{
	CEnemy::Render();
}

void SubFlyingEnemy::Destroy()
{
	CEnemy::Destroy();
}
