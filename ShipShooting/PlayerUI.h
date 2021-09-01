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

	Player* player = NULL;

	PlayerUI(Player* player);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

