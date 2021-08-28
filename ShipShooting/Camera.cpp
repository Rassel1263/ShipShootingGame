#include "Header.h"
#include "Camera.h"

void Camera::Init()
{
	divideProj = 1.5f;

	D3DXVECTOR3 vEyePt = { 0.0f, 0.0f, -20.0f };
	D3DXVECTOR3 vLookatPt = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 vUpVec = { 0.0f, 1.0f, 0.0f };
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	Game::GetInstance().pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixOrthoLH(&matProj, Game::GetInstance().screenWidth / divideProj, Game::GetInstance().screenHeight / divideProj, 0.01f, 1000.0f);
	Game::GetInstance().pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Camera::Update(float deltaTime)
{
	D3DXVec2Lerp(&cameraPos, &destCameraPos, &cameraPos, 0.1f);
	D3DXVec2Lerp(&cameraScale, &destCameraScale, &cameraScale, 0.1f);
	D3DXVec2Lerp(&cameraQuaken, &destCameraQuaken, &cameraQuaken, 0.1f);

	D3DXMatrixTranslation(&matWorld, (rand() % 2 ? 1 : -1) * cameraQuaken.x - cameraPos.x, (rand() % 2 ? 1 : -1) * cameraQuaken.y - cameraPos.y, 0.0f);
	Game::GetInstance().pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
}
