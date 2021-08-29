#pragma once

class Unit : public Object
{
public:
	struct UnitAbility
	{
		float hp = 0.0f;
		float maxHp = 0.0f;
		float speed = 0.0f;
	} ability;

	Sprite spr;
	RenderInfo ri;
	Unit();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) = 0;
	void SetAbility(float hp, float speed);
	D3DXVECTOR2 CheckPos();
};

