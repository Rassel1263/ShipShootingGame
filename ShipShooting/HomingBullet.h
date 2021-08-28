#pragma once
#include "CBullet.h"

class HomingBullet : public CBullet
{
public:
	float homingTime = 0.0f;
	
	float rotate = 0.0f;


	HomingBullet(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

