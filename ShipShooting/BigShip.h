#pragma once

class BigShip : public FloatingEnemy
{
public:
	bool intro = true;

	float restTime = 0.0f;
	float restTimer = 0.0f;

	float attackSpeed = 0.0f;
	float shootInterval = 0.0f;

	float outroTime = 0.0f;
	float effectTime = 0.0f;
	float effectTimer = 0.0f;
	int effectAmount = 0;

	int pattern = 0;

	Sprite cannon;
	std::vector<RenderInfo> cannonInfo;

	Sprite turret;
	std::vector<RenderInfo> turretInfo;

	Sprite machinegun;
	std::vector<RenderInfo> machinegunInfo;

public:
	BigShip(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ChoosePattern();
	void UpdatePattern(float deltaTime);
	void WeaponPos();
	void WeaponRender(Sprite weapon, std::vector<RenderInfo> weaponInfo);
	void WeaponRotate(std::vector<RenderInfo>& weaponInfo);
	float GetAngleToTarget(D3DXVECTOR2 targetPos);
	bool Intro(float deltaTime);
	bool Outro(float deltaTime);
	bool Pattern1(float deltaTime);
	bool Pattern2(float deltaTime);
	bool Pattern3(float deltatime);
};

