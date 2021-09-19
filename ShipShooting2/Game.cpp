#include "DXUT.h"
#include "Game.h"

Scene* nowScene = NULL;

void Game::Check()
{
#ifdef _DEBUG
	screenHeight = 1040;
#endif
}

Game::~Game()
{
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pLine);
}

HRESULT Game::Init()
{
	if (FAILED(DXUTGetD3D9Device()->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4, 0,
		D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB, 0)))
	{
		return E_FAIL;
	}

	D3DXCreateLine(DXUTGetD3D9Device(), &pLine);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_LIGHTING, FALSE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_ZENABLE, TRUE);

	DXUTGetD3D9Device()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DXUTGetD3D9Device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	ChangeScene(new GameScene());

	Camera::GetInstance().Init();
	Input::GetInstance().Start();
}
 
void Game::Update(float deltaTime)
{
	Input::GetInstance().Update();

	if (nextScene)
	{
		SAFE_DELETE(nowScene);

		nowScene = nextScene;
		nowScene->Init();
		nextScene = NULL;
	}

	if (Input::GetInstance().KeyDown(VK_F2))
		pause = !pause;

	if (!pause)
	{
		if (nowScene)
			nowScene->Update(deltaTime * timeScale);
	}

	Camera::GetInstance().Update();
}

void Game::Render()
{
	Camera::GetInstance().Render();

	if (nowScene)
		nowScene->Render();

	D3DXMATRIX matProj;
	D3DXMatrixOrthoLH(&matProj, Game::GetInstance().screenWidth, Game::GetInstance().screenHeight, 0.01f, 1000.0f);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &matProj);

	if (nowScene)
		nowScene->UIRender();

}

void Game::DrawLine(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXMATRIX matrix, D3DCOLOR color)
{
	pLine->SetWidth(2.0f);
	pLine->Begin();
	D3DXVECTOR3 v[] = { D3DXVECTOR3(p1.x, p1.y, 0.0f), D3DXVECTOR3(p2.x, p2.y, 0.0f) };
	D3DXMATRIX retMat = matrix * Camera::GetInstance().matWorld * Camera::GetInstance().matView * Camera::GetInstance().matProj;
	pLine->DrawTransform(v, 2, &retMat, color);
	pLine->End();
}

void Game::Term()
{
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pLine);
}

void Game::ChangeScene(Scene* nextScene)
{
	this->nextScene = nextScene;
}
