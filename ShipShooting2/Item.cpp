#include "DXUT.h"
#include "Item.h"

Item::Item(D3DXVECTOR2 pos, int index)
{
	this->pos = pos;
	this->index = index;
	spr.LoadAll(L"Assets/Sprites/Item/" + std::to_wstring(index));

	CreateCollider(D3DXVECTOR2(-30, -30), D3DXVECTOR2(30, 30), L"item");
}

void Item::Update(float deltaTime)
{
	spr.Update(deltaTime);
}

void Item::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

void Item::OnCollision(Collider& coli)
{
	if (coli.tag == L"player")
	{
		nowScene->player->SetItemEffective(index);
		SoundManager::GetInstance().Play(L"item");
		nowScene->obm.AddObject(new ItemUI(index, pos));
		switch (index)
		{
		case 0:
			nowScene->msgBox->SpawnMsgBox(L"obtainMachinegun");
			break;
		case 1:
			nowScene->msgBox->SpawnMsgBox(L"obtainTorpedo");
			break;
		case 2:
			nowScene->msgBox->SpawnMsgBox(L"MissileReady");
			break;
		case 3:
			nowScene->msgBox->SpawnMsgBox(L"obtainBooster");
			break;
		case 4:
			nowScene->msgBox->SpawnMsgBox(L"obtainToolbox");
			break;
		case 5:
			nowScene->msgBox->SpawnMsgBox(L"obtainEventbox");
			break;
		}

		destroy = true;
	}
}
