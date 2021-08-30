#pragma once
class CBullet : public Object
{
public:
	float angle = 0.0f;

	Sprite spr;
	RenderInfo ri;
	
	Unit* target = NULL;

	CBullet(D3DXVECTOR2 pos, Unit* target);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void CreateEffect() {};
	void SetCollider(float left, float bottom, float right, float top);
};

