#include "Header.h"
#include "PlayerUI.h"
#include "Player.h"
#include "MachineGun.h"

PlayerUI::PlayerUI(Player* player)
{
	this->player = player;

	hpBck.LoadAll(L"Assets/Sprites/UI/hpBck.png");
	hp.LoadAll(L"Assets/Sprites/UI/hp.png");

	hp.bCamera = false;
	hpBck.bCamera = false;

	weapon.LoadAll(L"Assets/Sprites/UI/weapon.png");
	weapon.bCamera = false;

	for (int i = 0; i < 4; ++i)
	{
		weaponCools[i].LoadAll(L"Assets/Sprites/UI/weaponCool.png");
		weaponCools[i].bCamera = false;
	}

	weaponInfo[0].pos = { 361, -445 };
	weaponInfo[1].pos = { 530, -445 };
	weaponInfo[2].pos = { 696, -445 };
	weaponInfo[3].pos = { 860, -445 };

	for (int i = 0; i < 2; ++i)
	{
		skillCool[i].LoadAll(L"Assets/Sprites/UI/skillCool.png");
		skillCool[i].bCamera = false;
	}

	skillInfo[0].pos = { 452, -295 };
	skillInfo[1].pos = { 782, -295 };

	hpInfo.pos = { -650, -420 };
}

void PlayerUI::Update(float deltaTime)
{
	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;

	weaponCools[0].heightRatio = player->machineGun->reloadTimer / player->machineGun->reloadTime;

	if(Input::GetInstance().KeyDown(VK_LBUTTON))
		std::cout << Input::GetInstance().GetFixedMousePos().x << "       " << Input::GetInstance().GetFixedMousePos().y << std::endl;
}

void PlayerUI::Render()
{
	hp.Render(hpInfo);
	hpBck.Render(hpInfo);

	weapon.Render(RenderInfo{});

	for (int i = 0; i < 4; ++i)
	{
		if (i < 2)
			skillCool[i].Render(skillInfo[i]);

		weaponCools[i].Render(weaponInfo[i]);

	}

	
}
