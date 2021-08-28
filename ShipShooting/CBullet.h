#pragma once
class CBullet : public Object
{
public:
	float angle = 0.0f;

	Sprite spr;
	RenderInfo ri;

	CBullet(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

