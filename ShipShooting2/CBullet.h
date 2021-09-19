#pragma once
class CBullet : public Object
{
public:
	enum class BulletType
	{
		Machinegun,
		Cannon,
		Torpedo,
		Missile
	} type;

	float angle = 0.0f;

	Sprite spr;
	RenderInfo ri;
	Unit* target = NULL;
	
	float damage = 0.0f;

	CBullet(D3DXVECTOR2 pos, Unit* target, float damage);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void CreateEffect() {};
};

