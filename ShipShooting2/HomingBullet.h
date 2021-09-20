#pragma once
class HomingBullet : public CBullet
{
public:
	bool homing = false;

	float startTime = 0.0f;
	float turnTimer= 0.0f;
	float turnSpeed = 0.0f;

	HomingBullet(D3DXVECTOR2 pos, Unit* target, BulletType type, std::wstring team, float damage, float angle, float startTime = 0.5f);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void CreateEffect() override;
	void HomingSystem(float deltaTime);
};

