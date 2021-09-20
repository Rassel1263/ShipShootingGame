#include "DXUT.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(Player* player)
{
	this->player = player;

	SetSprite(L"base.png", base);
	SetSprite(L"speed.png", spdKey);
	SetSprite(L"weapon/allWeapon.png", weapons);

	for (int i = 0; i < 4; ++i)
		SetSprite(L"weapon/coolTime.png", weaponCools[i]);

	fontInfo[0].pos = { -875, -288 };
	fontInfo[1].pos = { -695, -288 };
	fontInfo[2].pos = { -875, -458 };
	fontInfo[3].pos = { -695, -458 };

	SetSprite(L"hp_outline.png", hpBck);
	SetSprite(L"hp_ingage.png", hp);


	spdKeyInfo.pos = { -498, -422 };
	hpInfo.pos = { -470, -200 };
}

void PlayerUI::Update(float deltaTime)
{
	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;

	for (int i = 0; i < 4; ++i)
		FontUpdate(bulletFont[i], player->weapons[i]->bulletAmount);

	D3DXVec2Lerp(&spdKeyInfo.pos, &spdKeyInfo.pos, &D3DXVECTOR2(-498, -464 + player->speedLevel * 42), 0.1f);
}

void PlayerUI::Render()
{
	base.Render(RenderInfo{});
	spdKey.Render(spdKeyInfo);
	weapons.Render(RenderInfo{ D3DXVECTOR2(-770, -330) });
	for (int i = 0; i < 4; ++i)
		FontRender(bulletFont[i], fontInfo[i]);

	hpBck.Render(hpInfo);
	hp.Render(hpInfo);

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
		vec[cnt].LoadAll(L"Assets/Sprites/ui/ingame/font/" + str.substr(cnt, 1) + L".png");
		vec[cnt].bCamera = false;
		cnt++;
	}

}

void PlayerUI::FontRender(std::vector<Sprite> vec, RenderInfo ri)
{
	int size = vec.size();

	for (int i = size - 1; i >= 0; --i)
	{
		RenderInfo tempInfo;
		tempInfo.scale = { 0.5, 0.5 };
		tempInfo.pos = ri.pos + D3DXVECTOR2(-15 * i, 0);
		vec[size - 1 - i].Render(tempInfo);
	}
}
