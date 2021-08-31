#pragma once
class Mine : public Object
{
public:
	Sprite spr;
	Sprite range;
	RenderInfo ri;

	Mine(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli);
};

