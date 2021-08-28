#include "Header.h"

Scene* nowScene = NULL;

void Game::Check()
{
#ifdef _DEBUG
	screenHeight = 1040;
#endif // _DEBUG

}

Game::~Game()
{
	if (pVB != NULL)
		pVB->Release();

	if (pd3dDevice != NULL)
		pd3dDevice->Release();

	if (pD3D != NULL)
		pD3D->Release();
}

HRESULT Game::Init(HWND hWnd)
{
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pd3dDevice)))
	{
		return E_FAIL;
	}

#ifdef _DEBUG
	if (!AllocConsole())
		return E_FAIL;

	FILE* fDummy;

	freopen_s(&fDummy, "CON", "r", stdin);
	freopen_s(&fDummy, "CON", "w", stdout);
	freopen_s(&fDummy, "CON", "w", stderr);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	if (FAILED(pd3dDevice->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4, 0,
		D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB, 0)))
	{
		return E_FAIL;
	}

	Camera::GetInstance().Init();
	// Turn off culling
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Turn off D3D lighting
	pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Turn on the zbuffer
	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	ChangeScene(new GameScene());
}

void Game::Update(float deltaTime)
{
	if (nextScene)
	{
		SAFE_DELETE(nowScene);

		nowScene = nextScene;
		nowScene->Init();
		nextScene = NULL;
	}

	if (nowScene)
		nowScene->Update(deltaTime);

	Input::GetInstance().Update();
	Camera::GetInstance().Update(deltaTime);
}

void Game::Render()
{
	// Clear the backbuffer and the zbuffer
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(pd3dDevice->BeginScene()))
	{
		if (nowScene)
			nowScene->Render();

		// End the scene
		pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void Game::ChangeScene(Scene* nextScene)
{
	this->nextScene = nextScene;
}
