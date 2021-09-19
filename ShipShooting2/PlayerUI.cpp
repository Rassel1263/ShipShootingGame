#include "DXUT.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(Player* player)
{
	this->player = player;

	SetSprite(L"base.png", base);
}

void PlayerUI::Update(float deltaTime)
{
}

void PlayerUI::Render()
{
	base.Render(RenderInfo{});
}

void PlayerUI::SetSprite(std::wstring name, Sprite& spr)
{
	spr.LoadAll(L"Assets/Sprites/ui/ingame/" + name);
	spr.bCamera = false;
}
