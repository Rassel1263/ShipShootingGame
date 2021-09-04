#pragma once
class Mine : public Object
{
public:
	Sprite spr;
	Sprite range;
	RenderInfo ri;

	int hp = 5;

	bool bHit = false;

	float hitTimer = 0.0f;
	float hitTime = 0.0f;

	Mine(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli);
	void Destroy(bool explosion);
};

