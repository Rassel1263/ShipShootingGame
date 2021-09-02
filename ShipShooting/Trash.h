#pragma once
class Trash : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	int hp = 3;

	bool bHit = false;

	float hitTimer = 0.0f;
	float hitTime = 0.0f;

	Trash(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

