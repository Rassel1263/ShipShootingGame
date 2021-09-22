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

	}
	else if (type == ObstalceType::MINE)
	{
		spr.LoadAll(L"Assets/Sprites/Obstacle/mine");
		bck.LoadAll(L"Assets/Sprites/Obstacle/mineRange.png");

		CreateCollider(D3DXVECTOR2(-150, -80), D3DXVECTOR2(150, 80), L"obstacle");

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
	}

	colorShader = new ColorShader();
}

void Obstacle::Update(float deltaTime)
{
	//if (hp <= 0)
	//	Destroy();

	//if (hit)
	//{
	//	hitTimer += deltaTime;
	//	if (hitTimer >= hitTime)
	//	{
	//		hitTimer = 0.0f;
	//		hit = false;
	//	}
	//}

	if (pos.y < Camera::GetInstance().cameraPos.y - 600)
		destroy = true;

	spr.Update(deltaTime);
}

void Obstacle::Render()
{
	ri.pos = pos;

	if (type == Obstacle::ObstalceType::MINE)
		bck.Render(ri);

	if (hit)
		colorShader->Render(colorShader, spr, ri);
	else
		spr.Render(ri);

	Object::Render();
}

void Obstacle::OnCollision(Collider& coli)
{
	if (coli.tag == L"player")
	{
		if (type == Obstacle::ObstalceType::MINE)
			Destroy();
	}

	if (coli.tag == L"allybullet" || coli.tag == L"enemybullet")
	{
		if (static_cast<CBullet*>(coli.obj)->type == CBullet::BulletType::Torpedo &&
			type == ObstalceType::GARBAGE)
			destroy = true;

		/*if (!hit)
		{
			hp -= static_cast<CBullet*>(coli.obj)->damage;
			hit = true;
		}*/
	}
}

void Obstacle::Destroy()
{
	if (type == Obstacle::ObstalceType::MINE)
		nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.6, 0.6), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));

	destroy = true;

	if (!nowScene->GetRandomNumber(0, 4))
		nowScene->obm.AddObject(new Item(pos, nowScene->GetRandomNumber(0, 5)));
}
