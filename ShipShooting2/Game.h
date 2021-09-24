#pragma once

struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR color;
	D3DXVECTOR2 uv;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class Game : public Singleton<Game>
{
public:
	bool pause = false;

	float timeScale = 1.0f;
	float unscaleTime = 0.0f;

	int screenWidth = 1920;
	int screenHeight = 1080;

	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	LPD3DXLINE pLine = NULL;


	Scene* nextScene = NULL;

	void Check();
	~Game();

	HRESULT Init();
	void Update(float deltaTime);
	void Render();
	void DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color);
	void Term();
	void ChangeScene(Scene* nextScene);
};

