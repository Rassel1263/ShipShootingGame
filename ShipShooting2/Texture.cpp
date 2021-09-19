#include "DXUT.h"
#include "Texture.h"

namespace fs = std::filesystem;

TextureManager::~TextureManager()
{
	for (auto&tex : textures)
	{
		SAFE_RELEASE(tex.second->src);
		SAFE_DELETE(tex.second);
	}
}

void TextureManager::SaveFilePath()
{
	for (auto& file : fs::recursive_directory_iterator(L"Assets/Sprites"))
	{
		std::wstring filePath = fs::absolute(file.path());
		std::transform(filePath.begin(), filePath.end(), filePath.begin(), std::towlower);

		filePaths.push(filePath);
	}

	fileSize = filePaths.size();
}

void TextureManager::LoadTexture(int id)
{
	while (true)
	{
		std::wstring filePath;
		{
			std::lock_guard<std::mutex> guard(lock);

			if (filePaths.empty()) break;

			filePath = filePaths.front();
			filePaths.pop();
		}

		TextureManager::GetInstance().GetTexture(filePath);
	}

	++threadCnt;
}

const Texture* TextureManager::GetTexture(std::wstring filePath)
{
	filePath = fs::absolute(filePath);
	std::transform(filePath.begin(), filePath.end(), filePath.begin(), std::towlower);

	auto tf = textures.find(filePath);

	if (tf != textures.end()) 
		return tf->second;

	Texture* texture = new Texture;

	if (FAILED(D3DXCreateTextureFromFileExW(DXUTGetD3D9Device(),
		filePath.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
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

	return textures.insert(std::make_pair(filePath, texture)).first->second;
}

void TextureManager::Term()
{
	for (auto tex : textures)
	{
		SAFE_RELEASE(tex.second->src);
		SAFE_DELETE(tex.second);
	}
}
