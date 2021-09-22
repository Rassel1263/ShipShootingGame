#pragma once

enum class MINITAG
{
	PLAYER,
	ENEMY,
};

struct SpritePos
{
	MINITAG tag;
	D3DXVECTOR2* pos;
	Unit* parentUnit;
};

class MiniMap : public ObjectUI
{
public:
	float destColor = -1.0f;

	Sprite miniMap;

	std::map<MINITAG, Sprite> sprites;
	std::vector<SpritePos> miniObjects;

	MiniMap();

	void AddMiniObj(MINITAG tag, D3DXVECTOR2* pos, Unit* parent);
	virtual void Update(float deltaTime) override;
	virtual void Render();
	virtual void SortObj(Unit* obj);
};

