#pragma once
class PlayerUI : public ObjectUI
{
public:
	Sprite base;

	Sprite spdKey;
	RenderInfo spdKeyInfo;

	Sprite weapons;
	Sprite weaponCools[4];
	std::vector<Sprite> font[6];
	RenderInfo fontInfo[6];

	Sprite skills;
	Sprite focusEft;
	Sprite skillCools[2];

	Sprite hpBck;
	Sprite hp;

	Sprite invincible;
	Sprite speedUp;

	RenderInfo hpInfo;

	Player* player = NULL;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void SetSprite(std::wstring name, Sprite& spr);

	void FontUpdate(std::vector<Sprite>& vec, int& num);
	void FontRender(std::vector<Sprite> vec, RenderInfo ri, float kerning = 15);
};

