#pragma once
class AttackCollider : public Object
{
public:
	float time = 0.0f;
	float damage = 0.0f;

	AttackCollider(D3DXVECTOR2 pos, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, float time);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

