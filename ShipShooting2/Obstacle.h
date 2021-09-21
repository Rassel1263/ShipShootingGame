#pragma once

class Obstacle : public Object
{
public:
	enum class ObstalceType
	{
		GARBAGE,
		MINE,
		ROCK,
	} type;

	float hp = 0.0f;

	bool hit = false;
	bool hitTimer = 0.0f;
	bool hitTime = 0.1f;

	Sprite spr;
	RenderInfo ri;

	ColorShader* colorShader = NULL;

	Obstacle(D3DXVECTOR2 pos, ObstalceType type);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

