#pragma once

class Player : public Unit
{
public:
	Sprite spr;
	RenderInfo ri;

	std::vector<CWeapon*> weapons;

	float forwardAngle = 0.0f;

	int speedLevel = 1;

	Player();
	
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	void SetTarget(EnemyType enemyType);

	void CameraControll();
	void WeaponControll(float deltaTime);
};

