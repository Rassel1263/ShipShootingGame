#pragma once

// A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos; // The position
	D3DCOLOR color;    // The color
	D3DXVECTOR2 uv;
};


#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class Game : public Singleton<Game>
{
public:
	int screenWidth = 1920;
	int screenHeight = 1080;

	LPDIRECT3D9             pD3D = NULL; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       pd3dDevice = NULL; // Our rendering device
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL; // Buffer to hold vertices

	Scene* nextScene = NULL;


	void Check();

	virtual ~Game();
	HRESULT Init(HWND hWnd);
	void Update(float deltaTime);
	void Render();
	void ChangeScene(Scene* nextScene);
};

