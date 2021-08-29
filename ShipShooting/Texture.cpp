#include "Header.h"
#include "Texture.h"

TextureManager::~TextureManager()
{
    for (auto& tex : textures)
    {
        SAFE_RELEASE(tex.second->src);
        SAFE_DELETE(tex.second);
    }
}

const Texture* TextureManager::GetTexture(std::wstring filePath)
{
    auto tf = textures.find(filePath);
    
    if (tf != textures.end())
        return tf->second;

    Texture* texture = new Texture;

    if (FAILED(D3DXCreateTextureFromFileExW(Game::GetInstance().pd3dDevice,
        filePath.c_str(),
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        0,
        0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        &texture->info,
        0,
        &texture->src)))
    {
        delete texture;
        return nullptr;
    }

    return textures.insert({ filePath, texture }).first->second;
}
