#pragma once
class FlyingEnemy : public CEnemy
{
public:
	FlyingEnemy(D3DXVECTOR2 pos);

	bool setAirPos = true;
	float airPos = 0.0f;

	ColorShader* shadow = NULL;

	RenderInfo shadowRI;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Destroy() override;
	virtual bool Move(float deltaTime) override;
	
	virtual void Attack(float deltaTime) override;
};

