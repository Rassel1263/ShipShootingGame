#pragma once
class Effect : public Object
{
public:
	D3DXVECTOR2* fallowPos = NULL;

	float visibleTime = 0.0f;
	float maxVisibleTime = 0.0f;

	int index = 0;

	std::function<void()> func = NULL;

	Sprite spr;
	RenderInfo ri;

	Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, int index, bool bCamera, float aniTime, float rotate = 0 , std::function<void()> func = NULL);
	Effect(std::wstring eftName, D3DXVECTOR2* pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float aniTime, float rotate = 0 , std::function<void()> func = NULL);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

};

