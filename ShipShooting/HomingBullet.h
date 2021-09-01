#pragma once
#include "CBullet.h"

class HomingBullet : public CBullet
{
public:
	float startTime = 0.0f;
	float turnSpeed = 0.0f;
	float turnTime = 0.0f;


	HomingBullet(D3DXVECTOR2 pos, Unit* target, float damage, float angle);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void CreateEffect() override;
	void HomingSystem(float deltaTime);
};

