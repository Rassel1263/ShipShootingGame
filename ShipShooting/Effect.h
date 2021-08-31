#pragma once
class Effect : public Object
{
public:
	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;

	int index = 0;

	std::function<void()> func = NULL;

	Sprite spr;
	RenderInfo ri;

	Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float aniTime, float rotate, std::function<void()> func = 0);
	Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float aniTime, float visibleTime, float rotate = 0, std::function<void()> func = 0);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

