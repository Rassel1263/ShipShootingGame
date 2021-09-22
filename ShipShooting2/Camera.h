#pragma once
class Camera : public Singleton<Camera>
{
public:
	float divideProj = 1.0f;
	float destDivideProj = divideProj;

	D3DXMATRIX matView;
	D3DXMATRIX matWorld;
	D3DXMATRIX matProj;

	D3DXVECTOR2 cameraPos = { 0, 0 };
	D3DXVECTOR2 cameraScale = { 1, 1 };
	D3DXVECTOR2 cameraQuaken = { 0, 0 };
	D3DXVECTOR2 destCameraPos = cameraPos;
	D3DXVECTOR2 destCameraScale = cameraScale;
	D3DXVECTOR2 destCameraQuaken = cameraQuaken;

	D3DXVECTOR2 limitPos = { 0, 0 };
public:
	void Init();
	void Update();
	void Render();
};

