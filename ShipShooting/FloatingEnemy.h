#pragma once
#include "CEnemy.h"

class FloatingEnemy : public CEnemy
{
public:


	FloatingEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Destroy() override;
	virtual void OnCollision(Collider& coli) override;

};

