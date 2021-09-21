#pragma once
class ItemUI : public ObjectUI
{
public:
	Sprite spr;
	RenderInfo ri;

	bool draw = true;

	ItemUI(int index, D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

