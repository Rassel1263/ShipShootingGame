#pragma once

enum class MINITAG
{
	PLAYER,
	ENEMY,
	END,
};

struct SpritePos
{
	MINITAG tag;
	D3DXVECTOR2* pos;
	Object* parentObj;
};

class MiniMap : public Singleton<MiniMap>
{
public:
	Sprite minimap;

	std::map<MINITAG, Sprite> sprites;
	std::vector<SpritePos> miniObjects;
	std::vector<SpritePos> addObjects;

	void Init();
	void AddMiniObject(MINITAG tag, D3DXVECTOR2* pos, Object* parentObj);
	void Update(float deltaTime);
	void Render();
	void Term(Object* obj);
	void ChangeScene();
};

