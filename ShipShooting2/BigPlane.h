#pragma once
class BigPlane : public FlyingEnemy
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

	int gunIndex = 0;

	int pattern = 0;

	struct WeaponInfo
	{
		RenderInfo ri;
		int gunRenderNum = 0;
	};

	std::vector<Sprite> bGun;
	std::vector<WeaponInfo> bGunInfo;

	std::vector<Sprite> sGun;
	std::vector<WeaponInfo> sGunInfo;

public:
	BigPlane(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Destroy() override;
	virtual bool Move(float deltaTime) override;
	void ChoosePattern();
	void UpdatePattern(float deltaTime);
	void SetWeaponRotate(WeaponInfo& info, int rotate);
	void WeaponRender(std::vector<Sprite>& weapon, std::vector<WeaponInfo>& weaponInfo);

	bool Intro(float deltaTime);
	bool Outro(float deltaTime);
	bool Pattern1(float deltaTime);
	bool Pattern2(float deltaTime);
	bool Pattern3(float deltaTime);
};

