#include "DXUT.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(Player* player)
{
	this->player = player;

	SetSprite(L"base.png", base);
	SetSprite(L"speed.png", spdKey);
	spdKeyInfo.pos = { -498, -422 };
	SetSprite(L"weapon/allWeapon.png", weapons);

	// 무기 
	for (int i = 0; i < 4; ++i)
	{
		SetSprite(L"weapon/coolTime.png", weaponCools[i]);
		fontInfo[i].scale = D3DXVECTOR2(0.5, 0.5);
	}

	// 총알 개수
	fontInfo[0].pos = { -875, -288 };
	fontInfo[1].pos = { -695, -288 };
	fontInfo[2].pos = { -875, -458 };
	fontInfo[3].pos = { -695, -458 };

	// 이동속도
	fontInfo[4].pos = D3DXVECTOR2(spdKeyInfo.pos.x + 40, spdKeyInfo.pos.y);
	fontInfo[4].scale = { 0.4 ,0.4 };

	// 이동 거리
	fontInfo[5].pos = { -800, -50};

	// 체력바
	SetSprite(L"hp_outline.png", hpBck);
	SetSprite(L"hp_ingage.png", hp);
	SetSprite(L"speedUp.png", speedUp);
	SetSprite(L"invincible.png", invincible);
	hpInfo.pos = { -470, -200 };

	// 스킬

	SetSprite(L"skill1.png", skills[0]);
	SetSprite(L"skill2.png", skills[1]);

	for (int i = 0; i < 2; ++i)
		SetSprite(L"skills/skillCool.png", skillCools[i]);

	skillInfo[0].pos = { D3DXVECTOR2(-735, -130) };
	skillInfo[1].pos = { D3DXVECTOR2(-665, -130) };
}

void PlayerUI::Update(float deltaTime)
{
	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;
	speedUp.widthRatio = player->speedUpTime / 5.0f;
	invincible.widthRatio = player->invincibleTime / 2.0f;

	// 무기 총알 개수
	for (int i = 0; i < 6; ++i)
	{
		if (i < 4)
			FontUpdate(font[i], player->weapons[i]->bulletAmount);
		else if (i == 4)
		{
			int speed = (int)player->ability.speed / 5;
			FontUpdate(font[i], speed);
		}
		else if (i == 5)
		{
			int remainDistance = nowScene->destination - (int)player->moveDistance;
			FontUpdate(font[i], remainDistance);
		}
	}

	// 무기 장전 && 연사
	weaponCools[0].heightRatio = 1 - static_cast<MachineGun*>(player->weapons[0])->reloadTimer / static_cast<MachineGun*>(player->weapons[0])->reloadTime;
	weaponCools[1].heightRatio = 1 - static_cast<NavalGun*>(player->weapons[1])->reloadTimer / static_cast<NavalGun*>(player->weapons[1])->reloadTime;
	weaponCools[2].heightRatio = player->weapons[2]->shootTimer / player->weapons[2]->shootInterval;
	weaponCools[3].heightRatio = player->weapons[3]->shootTimer / player->weapons[3]->shootInterval;

	// 스킬 쿨타임
	skillCools[0].heightRatio = 1 - player->skill1CoolTime / 10.0f;
	skillCools[1].heightRatio = 1 - player->skill2CoolTime / 20.0f;

	D3DXVec2Lerp(&spdKeyInfo.pos, &spdKeyInfo.pos, &D3DXVECTOR2(-498, -464 + player->speedLevel * 42), 0.1f);
	fontInfo[4].pos = D3DXVECTOR2(spdKeyInfo.pos.x + 40, spdKeyInfo.pos.y);

}

void PlayerUI::Render()
{
	base.Render(RenderInfo{});
	spdKey.Render(spdKeyInfo);

	// 무기
	weapons.Render(RenderInfo{ D3DXVECTOR2(-770, -330) });

	for (int i = 0; i < 6; ++i)
	{
		if (i < 4)
			FontRender(font[i], fontInfo[i]);
		else if (i == 4)
			FontRender(font[i], fontInfo[i], 10);
		else if (i == 5)
			FontRender(font[i], fontInfo[i], 30);
	}

	weaponCools[0].Render(RenderInfo{ D3DXVECTOR2(-860, -247) });
	weaponCools[1].Render(RenderInfo{ D3DXVECTOR2(-681, -247) });
	weaponCools[2].Render(RenderInfo{ D3DXVECTOR2(-860, -417) });
	weaponCools[3].Render(RenderInfo{ D3DXVECTOR2(-681, -417) });

	// 스킬
	for (int i = 0; i < 2; ++i)
	{
		skills[i].Render(skillInfo[i]);
		skillCools[i].Render(skillInfo[i]);
	}

	hpBck.Render(hpInfo);
	hp.Render(hpInfo);
	speedUp.Render(hpInfo);
	invincible.Render(hpInfo);
}

void PlayerUI::SetSprite(std::wstring name, Sprite& spr)
{
	spr.LoadAll(L"Assets/Sprites/ui/ingame/" + name);
	spr.bCamera = false;
}

void PlayerUI::FontUpdate(std::vector<Sprite>& vec, int& num)
{
	std::wstring str = std::to_wstring(num);

	int size = str.size();
	vec.resize(size);

	int cnt = 0;
	for (auto s : str)
	{
		vec[cnt].LoadAll(L"Assets/Sprites/ui/Font/Number/" + str.substr(cnt, 1) + L".png");
		vec[cnt].bCamera = false;
		cnt++;
	}

}

void PlayerUI::FontRender(std::vector<Sprite> vec, RenderInfo ri, float kerning)
{
	int size = vec.size();

	for (int i = size - 1; i >= 0; --i)
	{
		RenderInfo tempInfo;
		tempInfo.scale = ri.scale;
		tempInfo.pos = ri.pos + D3DXVECTOR2(-kerning * i, 0);
		vec[size - 1 - i].Render(tempInfo);
	}
}
