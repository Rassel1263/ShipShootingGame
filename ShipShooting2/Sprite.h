#pragma once

struct RenderInfo
{
	D3DXVECTOR2 pos = { 0, 0 };
	D3DXVECTOR2 pivot = { 0.5, 0.5 };
	D3DXVECTOR2 scale = { 1, 1 };
	float rotate = 0.0f;
};

class Sprite
{
public:
	bool bAnimation = true;
	bool bAniLoop = true;
	bool bAniStop = false;
	bool bCamera = true;

	float aniTime = 0.0f;
	float aniMaxTime = 0.1f;

	float widthRatio = 1.0f;
	float heightRatio = 0.0f;

	int scene = 0;
	int szScene = 0;

	D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);

	std::vector<const Texture*> textures;

	void LoadAll(std::wstring filePath, float aniMaxTime = 0.1f, bool aniLoop = true);
	void Update(float deltaTime);
	void Render(RenderInfo& ri);
	const Texture* GetNowScene();

	void Reset();
};

