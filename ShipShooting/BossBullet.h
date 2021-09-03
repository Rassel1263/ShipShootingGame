#pragma once
#include "CBullet.h"

class BossBullet : public CBullet
{
public:
	enum class Type
	{
		Machinegun,
		Torpedo,
		Missile,
	} type;

	bool homing = false;

	float homingTime = 0.0f;

	float startTime = 0.0f;
	float turnSpeed = 0.0f;
	float turnTime = 0.0f;

	BossBullet(D3DXVECTOR2 pos, float angle, float damage, Type type);
	BossBullet(D3DXVECTOR2 pos, float angle, float startTime, float homingTime, float damage);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void CreateEffect() override;
	void HomingSystem(float deltaTime);

};

