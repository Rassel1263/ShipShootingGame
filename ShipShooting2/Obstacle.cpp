#include "DXUT.h"
#include "Obstacle.h"

Obstacle::Obstacle(D3DXVECTOR2 pos, ObstalceType type)
{
	this->pos = pos;
	this->type = type;
	if (type == ObstalceType::GARBAGE)
	{
		int index = nowScene->GetRandomNumber(1, 2);
		spr.LoadAll(L"Assets/Sprites/Obstacle/Garbage/" + std::to_wstring(index));

		CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"obstacle");

		hp = 10.0f;
	}
	else if (type == ObstalceType::MINE)
	{
		spr.LoadAll(L"Assets/Sprites/Obstacle/mine");

		CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"obstacle");

		hp = 20.0f;
	}
	else if (type == ObstalceType::ROCK)
	{
		int index = nowScene->GetRandomNumber(0, 3);
		spr.LoadAll(L"Assets/Sprites/Obstacle/rock/" + std::to_wstring(index) + L".png");

		if(index == 0)
			CreateCollider(D3DXVECTOR2(-250, -140), D3DXVECTOR2(250, 140), L"obstacle");
		else if(index == 1)
			CreateCollider(D3DXVECTOR2(-234, -180), D3DXVECTOR2(234, 180), L"obstacle");
		else if (index == 2)
			CreateCollider(D3DXVECTOR2(-240, -130), D3DXVECTOR2(240, 130), L"obstacle");
		else if(index == 3)
			CreateCollider(D3DXVECTOR2(-40, -30), D3DXVECTOR2(40, 30), L"obstacle");
		hp = 50.0f;
	}

	colorShader = new ColorShader();
}

void Obstacle::Update(float deltaTime)
{
	if (hit)
	{
		hitTimer += deltaTime;
		if (hitTimer >= hitTime)
		{
			hitTimer = 0.0f;
			hit = false;
		}
	}

	spr.Update(deltaTime);
}

void Obstacle::Render()
{
	ri.pos = pos;

	if (hit)
		colorShader->Render(colorShader, spr, ri);
	else
		spr.Render(ri);

	Object::Render();
}

void Obstacle::OnCollision(Collider& coli)
{
	if (coli.tag == L"allybullet" || coli.tag == L"enemybullet")
	{
		if (!hit)
		{
			hp -= static_cast<CBullet*>(coli.obj)->damage;
			hit = true;
		}
	}
}
