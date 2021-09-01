#pragma once
class Font : public Object
{
public:
	float& num;
	float kerning = 0.0f;
	bool update = false;

	std::vector<Sprite> fonts;

	RenderInfo ri;

	Font(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float kerning, float& num, bool update = true);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

