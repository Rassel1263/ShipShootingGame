#pragma once
#include "CBullet.h"

class MachinegunBullet : public CBullet
{
public:
	MachinegunBullet(D3DXVECTOR2 pos, Unit* target, float damage);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void CreateEffect() override;
	virtual void OnCollision(Collider& coli) override;
};

