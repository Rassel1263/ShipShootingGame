#include "Header.h"
#include "Trash.h"

Trash::Trash(D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/Obstacle/trash.png");
	this->pos = pos;

	layer = 4;
}

void Trash::Update(float deltaTime)
{
	pos.y -= nowScene->player->ability.speed / 3 * deltaTime;
}

void Trash::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

void Trash::OnCollision(Collider& coli)
{
	if (coli.tag == L"allybullet")
	{
		if (!bHit)
		{
			hp--;
			bHit = true;
		}
	}
}
