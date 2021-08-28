#include "Header.h"
#include "Sprite.h"
namespace fs = std::filesystem;

void Sprite::LoadAll(std::wstring filePath, float aniMaxTime, bool aniLoop)
{
	textures.clear();

	if (fs::is_directory(filePath))
	{
		for (auto file : fs::recursive_directory_iterator(filePath))
		{
			if (auto texture = TextureManager::GetInstance().GetTexture(file.path()))
				textures.push_back(texture);
		}
	}
	else
	{
		if (auto texture = TextureManager::GetInstance().GetTexture(filePath))
			textures.push_back(texture);
		else
			textures.push_back(TextureManager::GetInstance().GetTexture(L"banana.bmp"));
	}

	this->aniMaxtime = aniMaxTime;
	this->bAniLoop = aniLoop;
	szScene = (int)textures.size();
}

void Sprite::Update(float deltaTime)
{
	if (!bAnimation)
		return;

	aniTime += deltaTime;

	if (aniTime > aniMaxtime)
	{
		aniTime = 0.0f;

		if (scene < szScene - 1)
			scene++;
		else if (bAniLoop)
			scene = 0;
		else
			bAnimation = false;
	}
}

void Sprite::Render(const RenderInfo& ri)
{
	CUSTOMVERTEX* pVertices = nullptr;

	Game::GetInstance().pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVertices[0].color = color;
	pVertices[0].uv = D3DXVECTOR2(0.0f, 1.0f);

	pVertices[1].pos = D3DXVECTOR3(0.0f, GetNowScene()->info.Height * (1.0f - heightRatio), 0.0f);
	pVertices[1].color = color;
	pVertices[1].uv = D3DXVECTOR2(0.0f, heightRatio);

	pVertices[2].pos = D3DXVECTOR3(GetNowScene()->info.Width * widthRatio, 0.0f, 0.0f);
	pVertices[2].color = color;
	pVertices[2].uv = D3DXVECTOR2(1.0f * widthRatio, 1.0f);

	pVertices[3].pos = D3DXVECTOR3(GetNowScene()->info.Width * widthRatio, GetNowScene()->info.Height * (1.0f - heightRatio), 0.0f);
	pVertices[3].color = color;
	pVertices[3].uv = D3DXVECTOR2(1.0f * widthRatio, heightRatio);

	Game::GetInstance().pVB->Unlock();

	D3DXMATRIX matrix;
	D3DXVECTOR2 centerPos = D3DXVECTOR2(GetNowScene()->info.Width * ri.pivot.x, GetNowScene()->info.Height * ri.pivot.y);
	D3DXMatrixTransformation2D(&matrix, &centerPos, 0, &ri.scale, &centerPos, -D3DXToRadian(ri.rotate), &(ri.pos - centerPos));

	Game::GetInstance().pd3dDevice->SetTransform(D3DTS_WORLD, (bCamera) ? &matrix : &(matrix * Camera::GetInstance().matWorld));
	Game::GetInstance().pd3dDevice->SetTexture(0, GetNowScene()->src);
	Game::GetInstance().pd3dDevice->SetStreamSource(0, Game::GetInstance().pVB, 0, sizeof(CUSTOMVERTEX));
	Game::GetInstance().pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	Game::GetInstance().pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

const Texture* Sprite::GetNowScene()
{
	return textures[scene];
}
