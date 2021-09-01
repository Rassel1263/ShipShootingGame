#pragma once

enum class Team
{
	None,
	Ally,
	Enemy,
};

class Unit : public Object
{
public:
	struct UnitAbility
	{
		float hp = 0.0f;
		float maxHp = 0.0f;
		float speed = 0.0f;
	} ability;

	Team team = Team::Ally;

	Sprite spr;
	RenderInfo ri;

	Unit* target = NULL;

	bool bHit = false;

	float hitTimer = 0.0f;
	float hitTime = 0.0f;
	float hitDamage = 0.0f;

	Unit();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) = 0;
	virtual void Hit(float damage) = 0;
	void SetAbility(float hp, float speed);
	void SetCollider(float left, float bottom, float right, float top, std::wstring tag);
	//void SetCollider(float radius, std::wstring tag);
	D3DXVECTOR2 CheckPos();
};

