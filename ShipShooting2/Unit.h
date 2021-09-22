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

		void SetAbility(float hp, float speed)
		{
			this->hp = hp;
			this->maxHp = hp;
			this->speed = speed;
		}
	} ability;

	Unit* target = NULL;
	ColorShader* colorShader = NULL;

	Team team = Team::None;

	std::vector<Sprite> sprites;
	RenderInfo ri;

	bool hit = false;
	float hitTimer = 0.0f;
	float hitTime = 0.0f;

	// ¹è È¸Àü 
	float curRadian = 0.0f;
	float curRotate = 0.0f;
	float rotateSpd = 0.0f;

	int renderNum = 0;
	int fixAni = 0;

	// ±ôºýÀÓ


	Unit();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual bool Move(float deltaTime);
	virtual void Hit(float damage);

	void SetAni(float rotate, bool bigPlane = false);

	Sprite& GetNowSprite();

	template <typename T>
	void SetAni(T n)
	{
		renderNum = IntEnum(n);
		GetNowSprite().Reset();
	}

	template <typename T>
	void Resize(T n)
	{
		sprites.resize(IntEnum(n));
	}

	template <typename T>
	Sprite& GetSprite(T n)
	{
		return sprites.at(IntEnum(n));
	}

};

