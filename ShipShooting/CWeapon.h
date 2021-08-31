#pragma once
#include "Effect.h"

class Unit;
class CWeapon : public Object
{
public:
	bool reload = false;

	int bulletAmount = 0.0f;
	int bulletMaxAmount = 0.0f;

	float shootInterval = 0.0f;
	float shootTimer = 0.0f;

	float reloadTime = 0.0f;
	float reloadTimer = 0.0f;
	
	float damage = 0.0f;

	Unit* owner = NULL;
	D3DXVECTOR2 offset;

	Sprite spr;
	RenderInfo ri;

	CWeapon(Unit* owner, D3DXVECTOR2 offset);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Shoot();
};

