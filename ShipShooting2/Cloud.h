#pragma once
class Cloud : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float speed = 0.0f;

	Cloud(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

