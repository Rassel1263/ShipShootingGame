#include "DXUT.h"
#include "Sprite.h"

namespace fs = std::filesystem;

void Sprite::LoadAll(std::wstring filePath, float aniMaxTime, bool aniLoop)
{
    textures.clear();

    if (fs::is_directory(filePath))
    {
        for (auto& file : fs::recursive_directory_iterator(filePath))
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
            textures.push_back(TextureManager::GetInstance().GetTexture(L"ShipShooting2.jpg"));
    }

    this->aniMaxTime = aniMaxTime;
    this->bAniLoop = aniLoop;
    this->szScene = (int)textures.size();
}

void Sprite::Update(float deltaTime)
{
    if (!bAnimation || bAniStop) return;

    aniTime += deltaTime;

    if (aniTime > aniMaxTime)
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

void Sprite::Render(RenderInfo& ri)
{
    CUSTOMVERTEX* v = NULL;

    Game::GetInstance().pVB->Lock(0, 0, (void**)&v, 0);

    v[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    v[0].color = color;
    v[0].uv = D3DXVECTOR2(0.0f, 1.0f);

    v[1].pos = D3DXVECTOR3(0.0f, GetNowScene()->info.Height * (1.0f - heightRatio), 0.0f);
    v[1].color = color;
    v[1].uv = D3DXVECTOR2(0.0f, heightRatio);

    v[2].pos = D3DXVECTOR3(GetNowScene()->info.Width * widthRatio, 0.0f, 0.0f);
    v[2].color = color;
    v[2].uv = D3DXVECTOR2(1.0f * widthRatio, 1.0f);

    v[3].pos = D3DXVECTOR3(GetNowScene()->info.Width * widthRatio, GetNowScene()->info.Height * (1.0f - heightRatio), 0.0f);
    v[3].color = color;
    v[3].uv = D3DXVECTOR2(1.0f * widthRatio, heightRatio);

    Game::GetInstance().pVB->Unlock();

    D3DXMATRIX matrix;
    D3DXVECTOR2 centerPos = D3DXVECTOR2(GetNowScene()->info.Width * ri.pivot.x, GetNowScene()->info.Height * ri.pivot.y);
    D3DXMatrixTransformation2D(&matrix, &centerPos, 0, &ri.scale, &centerPos, D3DXToRadian(-ri.rotate), &(ri.pos - centerPos));

    DXUTGetD3D9Device()->SetTransform(D3DTS_WORLD, (bCamera) ? &(matrix * Camera::GetInstance().matWorld) : &matrix);
    DXUTGetD3D9Device()->SetTexture(0, GetNowScene()->src);
    DXUTGetD3D9Device()->SetStreamSource(0, Game::GetInstance().pVB, 0, sizeof(CUSTOMVERTEX));
    DXUTGetD3D9Device()->SetFVF(D3DFVF_CUSTOMVERTEX);
    DXUTGetD3D9Device()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

const Texture* Sprite::GetNowScene()
{
    return textures[scene];
}

void Sprite::Reset()
{
    scene = 0;
    bAnimation = true;
    aniTime = 0.0f;
}
