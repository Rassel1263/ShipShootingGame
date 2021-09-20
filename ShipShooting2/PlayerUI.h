#pragma once
class PlayerUI : public ObjectUI
{
public:
	Sprite base;
	Sprite spdKey;
	Sprite weapons;

	Sprite hpBck;
	Sprite hp;
	RenderInfo hpInfo;

	RenderInfo spdKeyInfo;

	Player* player = NULL;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void SetSprite(std::wstring name, Sprite& spr);
};

