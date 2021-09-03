#pragma once
class HitBox : public Object
{
public:
	float time = 0.0f;
	float damage = 0.0f;

	HitBox(D3DXVECTOR2 pos, float left, float bottom, float right, float top, float damage, float time);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

