#pragma once

struct RenderInfo
{
	D3DXVECTOR2 pos = { 0.0f, 0.0f };
	D3DXVECTOR2 scale = { 1.0f, 1.0f };
	D3DXVECTOR2 pivot = { 0.5f, 0.5f };
	float rotate  =0;
};

class Sprite
{
public:
	bool bAnimation = true;
	bool bAniLoop = true;
	bool bCamera = false;

	int scene = 0;
	int szScene = 0;

	float aniTime = 0.0f;
	float aniMaxtime = 0.1f;

	float widthRatio = 1.0f;
	float heightRatio= 0.0f;

	D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);

	std::vector<const Texture*> textures;

	void LoadAll(std::wstring filePath, float aniMaxTime = 0.1f, bool bAniLoop = true);
	void Update(float deltaTime);
	void Render(const RenderInfo& ri); 
	const Texture* GetNowScene();
};

