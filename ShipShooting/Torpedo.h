#pragma once
#include "CBullet.h"

class Torpedo : public CBullet
{
public:
	float startTime = 0.0f;
	float turnSpeed = 0.0f;
	float turnTime = 0.0f;

	Torpedo(D3DXVECTOR2 pos, Unit* target);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void CreateEffect() override;
};

