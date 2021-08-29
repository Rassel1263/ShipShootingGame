#pragma once

struct Texture
{
	LPDIRECT3DTEXTURE9 src;
	D3DXIMAGE_INFO info;
};

class TextureManager : public Singleton<TextureManager>
{
	std::map<std::wstring, Texture*> textures;
public:
	~TextureManager();
	const Texture* GetTexture(std::wstring filePath);
};

