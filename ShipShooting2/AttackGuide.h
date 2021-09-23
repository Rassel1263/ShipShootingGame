#pragma once
class AttackGuide : public Object
{
public:
	Sprite bck;
	RenderInfo bckRI;

	int index = 0;

	float time = 0.0f;
	float maxTime = 0.0f;

	Sprite spr;
	RenderInfo ri;

	std::function<void()> func = NULL;

	AttackGuide(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float time, int index, std::function<void()> func = NULL);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

