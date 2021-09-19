#pragma once

struct Texture
{
	LPDIRECT3DTEXTURE9 src;
	D3DXIMAGE_INFO info;
};

class TextureManager : public Singleton<TextureManager>
{
private:
	std::mutex lock;
	std::map<std::wstring, Texture*> textures;

	std::queue<std::wstring> filePaths;

	int fileSize = 0;
	int threadCnt = 0;
public:
	~TextureManager();

	void SaveFilePath();
	void LoadTexture(int id);
	const Texture* GetTexture(std::wstring filePath);
	void Term();
};

