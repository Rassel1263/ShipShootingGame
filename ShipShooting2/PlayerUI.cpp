#include "DXUT.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(Player* player)
{
	this->player = player;

	SetSprite(L"base.png", base);
	SetSprite(L"speed.png", spdKey);
	SetSprite(L"weapon/allWeapon.png", weapons);

	SetSprite(L"hp_outline.png", hpBck);
	SetSprite(L"hp_ingage.png", hp);

	spdKeyInfo.pos = { -498, -422 };
	hpInfo.pos = { -470, -200 };
}

void PlayerUI::Update(float deltaTime)
{
	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;

	D3DXVec2Lerp(&spdKeyInfo.pos, &spdKeyInfo.pos, &D3DXVECTOR2(-498, -464 + player->speedLevel * 42), 0.1f);
}

void PlayerUI::Render()
{
	base.Render(RenderInfo{});
	spdKey.Render(spdKeyInfo);
	weapons.Render(RenderInfo{D3DXVECTOR2(-770, -330)});

	hpBck.Render(hpInfo);
	hp.Render(hpInfo);
}

void PlayerUI::SetSprite(std::wstring name, Sprite& spr)
{
	spr.LoadAll(L"Assets/Sprites/ui/ingame/" + name);
	spr.bCamera = false;
}
