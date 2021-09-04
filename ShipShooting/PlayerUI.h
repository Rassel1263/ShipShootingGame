#pragma once

class Player;
class PlayerUI : public Object
{
public:
	Sprite hp;
	Sprite hpBck;
	RenderInfo hpInfo;

	Sprite weapon;
	Sprite weaponCools[4];
	RenderInfo weaponInfo[4];

	Sprite skillCool[2];
	RenderInfo skillInfo[2];

	Sprite speed;
	Sprite speedBck;
	RenderInfo speedInfo;

	Sprite invincible;
	Sprite speedUp;
	Sprite speedIcon;
	Sprite invincibleIcon;

	Sprite speedDown;

	std::vector<Sprite> font[4];
	RenderInfo fontInfo[4];
	RenderInfo fontRI;

	Sprite progress;
	Sprite progressBck;
	Sprite progressObj;

	Player* player = NULL;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void FontUpdate(std::vector<Sprite>& vec, int& num);
	void FontRender(std::vector<Sprite>& vec, RenderInfo& ri);
};

