#include "Header.h"
#include "PlayerUI.h"
#include "Player.h"
#include "MachineGun.h"
#include "Cannon.h"
#include "MissileTurret.h"
#include "TorpedoLauncher.h"

PlayerUI::PlayerUI(Player* player)
{
	this->player = player;

	hpBck.LoadAll(L"Assets/Sprites/UI/hpBck.png");
	hp.LoadAll(L"Assets/Sprites/UI/hp.png");

	hp.bCamera = false;
	hpBck.bCamera = false;

	hpInfo.pos = { -650, -420 };

	speed.LoadAll(L"Assets/Sprites/UI/speed.png");
	speedBck.LoadAll(L"Assets/Sprites/UI/speedbck.png");

	speed.bCamera = false;
	speedBck.bCamera = false;

	speedUp.LoadAll(L"Assets/Sprites/UI/speedUp.png");
	invincible.LoadAll(L"Assets/Sprites/UI/invincible.png");
	
	speedDown.LoadAll(L"Assets/Sprites/UI/speedDown");

	speedIcon.LoadAll(L"Assets/Sprites/UI/sIcon.png");
	invincibleIcon.LoadAll(L"Assets/Sprites/UI/iIcon.png");
	speedIcon.bCamera = false;
	invincibleIcon.bCamera = false;

	speedUp.bCamera = false;
	invincible.bCamera = false;

	speedInfo.pos = { -440, -410 };

	weapon.LoadAll(L"Assets/Sprites/UI/weapon.png");
	weapon.bCamera = false;

	for (int i = 0; i < 4; ++i)
	{
		weaponCools[i].LoadAll(L"Assets/Sprites/UI/weaponCool.png");
		weaponCools[i].bCamera = false;
	}

	weaponInfo[0].pos = { 361, -445 };
	weaponInfo[1].pos = { 530, -445 };
	weaponInfo[2].pos = { 695, -445 };
	weaponInfo[3].pos = { 860, -445 };

	for (int i = 0; i < 2; ++i)
	{
		skillCool[i].LoadAll(L"Assets/Sprites/UI/skillCool.png");
		skillCool[i].bCamera = false;
	}

	skillInfo[0].pos = { 451, -297 };
	skillInfo[1].pos = { 782, -297};

	fontInfo[0].pos = { 340, -484 };
	fontInfo[1].pos = { 510, -484 };
	fontInfo[2].pos = { 680, -484 };
	fontInfo[3].pos = { 840, -481 };

	progressBck.LoadAll(L"Assets/Sprites/UI/progressBck.png");
	progressBck.bCamera = false;
	progress.LoadAll(L"Assets/Sprites/UI/progress.png");
	progress.bCamera = false;

	progressObj.LoadAll(L"Assets/Sprites/UI/progressObj.png");
	progressObj.bCamera = false;

	layer = 10;
}

void PlayerUI::Update(float deltaTime)
{
	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;

	speed.heightRatio = 1 - player->ability.speed / player->maxSpeed;

	weaponCools[0].heightRatio = 1- player->machineGun->reloadTimer / player->machineGun->reloadTime; 
	weaponCools[1].heightRatio = 1 - player->cannon->reloadTimer / player->cannon->reloadTime;
	weaponCools[2].heightRatio = player->torpedLauncher->shootTimer / player->torpedLauncher->shootInterval;
	weaponCools[3].heightRatio = player->turret->shootTimer / player->turret->shootInterval;

	skillCool[0].heightRatio = 1 - player->skill1CoolTime / 5.0f;
	skillCool[1].heightRatio = 1 - player->skill2CoolTime / 10.0f;

	speedUp.widthRatio = 1 - player->speedUpTime / 5.0f;
	invincible.widthRatio = 1 - player->invincibleTime / 2.0f;
	speedUp.heightRatio = hp.heightRatio;
	invincible.heightRatio = hp.heightRatio;

	FontUpdate(font[0], player->machineGun->bulletAmount);
	FontUpdate(font[1], player->cannon->bulletAmount);
	FontUpdate(font[2], player->torpedLauncher->bulletAmount);
	FontUpdate(font[3], player->turret->bulletAmount);

	progress.heightRatio = 1 - nowScene->progress / nowScene->maxProgress;

	speedDown.Update(deltaTime);
}

void PlayerUI::Render()
{
	hp.Render(hpInfo);
	hpBck.Render(hpInfo);

	if (player->speedUp)
	{
		speedIcon.Render(RenderInfo{D3DXVECTOR2(-920, -480)});
		speedUp.Render(hpInfo);
	}

	if (player->invincible)
	{
		invincibleIcon.Render(RenderInfo{ D3DXVECTOR2(-850, -480) });
		invincible.Render(hpInfo);
	}

	if (player->speedDown)
		speedDown.Render(RenderInfo{ player->pos });

	progressBck.Render(RenderInfo{ D3DXVECTOR2(-860, 0) });
	progress.Render(RenderInfo{ D3DXVECTOR2(-860, 0) });
	progressObj.Render(RenderInfo{D3DXVECTOR2(-860, -340 + (nowScene->progress / nowScene->maxProgress) * 675)});

	speedBck.Render(speedInfo);
	speed.Render(speedInfo);

	weapon.Render(RenderInfo{});

	for (int i = 0; i < 4; ++i)
		FontRender(font[i], fontInfo[i]);

	for (int i = 0; i < 4; ++i)
	{
		if (i < 2)
			skillCool[i].Render(skillInfo[i]);

		weaponCools[i].Render(weaponInfo[i]);
	}

}

void PlayerUI::FontRender(std::vector<Sprite>& vec, RenderInfo& ri)
{
	int size = vec.size();

	for (int i = size - 1; i >= 0; --i)
	{
		fontRI.pos = ri.pos + D3DXVECTOR2(-15 * i, 0);
		vec[size - 1 - i].Render(fontRI);
	}
}

void PlayerUI::FontUpdate(std::vector<Sprite>& vec, int& num)
{
	WCHAR temp[10];

	wsprintf(temp, L"%02d", (int)num);

	std::wstring str = temp;

	vec.resize(str.size());
	int count = 0;

	for (auto s : str)
	{
		vec[count].LoadAll(L"Assets/Sprites/UI/Font/SNumber/" + std::to_wstring(s - '0') + L".png");
		vec[count].bCamera = false;
		count++;
	}
}
 