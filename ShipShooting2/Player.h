#pragma once

class Player : public Unit
{
public:
	Sprite spr;
	RenderInfo ri;


	std::vector<CWeapon*> weapons;

	float forwardAngle = 0.0f;
	float dps = 0.0f;
	float moveDistance = 0.0f;


	float destSpeed = 0.0f;
	int speedLevel = 1;
	
	bool speedDown = 0.0f;
	float speedDownTime = 0.0f;

	bool fallowCamera = true;
	bool stop = true;

	// 아이템
	bool speedUp = false;
	float speedUpTime = 0.0f;
	
	bool god = false;
	bool invincible = false;
	float invincibleTime = 0.0f;

	// 스킬
	bool skill1 = false;
	bool skill1Msg = false;
	float skill1Timer = 0.0f;
	float skill1CoolTime = 10.0f;

	bool skill2Msg = false;
	float skill2CoolTime = 20.0f;

	bool drawGameOver = false;

	Player();
	
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual bool Move(float deltaTime) override;
	virtual void Hit(float damage);

	void SetTarget(EnemyType enemyType);
	void SetItemEffective(int index);
	void UpdateItemEffect(float deltaTime);
	void FirstSkillControll(float deltaTime);
	void SecondSkillControll(float deltaTime);

	void CameraControll();
	void WeaponControll(float deltaTime);
};

