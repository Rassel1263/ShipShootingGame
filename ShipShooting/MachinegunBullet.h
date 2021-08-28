#pragma once
#include "CBullet.h"

class MachinegunBullet : public CBullet
{
public:
	MachinegunBullet(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

