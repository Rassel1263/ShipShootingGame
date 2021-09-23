#include "DXUT.h"
#include "LoadSprite.h"

LoadSprite::LoadSprite()
{
	bck.LoadAll(L"Assets/Sprites/ui/outgame/intro/", 0.02f, false);

	loadingFrame.LoadAll(L"Assets/Sprites/ui/outgame/loading/gageback.png");
	loadingFrame.color.a = 0.0f;
	loadingBar.LoadAll(L"Assets/Sprites/ui/outgame/loading/gagemain.png");
	loadingBar.color.a = 0.0f;

	TextureManager::GetInstance().SaveFilePath();

	for (int i = 0; i < 12; ++i)
		threads.emplace_back(&TextureManager::LoadTexture, &TextureManager::GetInstance(), i);

	maxSize = TextureManager::GetInstance().GetFilePathSize();
}

LoadSprite::~LoadSprite()
{
	for (auto& thread : threads)
	{
		if (thread.joinable())
			thread.join();
	}
}

void LoadSprite::Update(float deltaTime)
{
	size = TextureManager::GetInstance().GetFilePathSize();

	if (TextureManager::GetInstance().GetThreadCount() >= 12)
	{
		loadingBar.color.a -= deltaTime;
		loadingFrame.color.a = loadingBar.color.a;

		if (loadingBar.color.a <= 0.0f)
		{
			nowScene->obm.AddObject(new Main());
			destroy = true;
		}
	}
	else
	{
		if (!bck.bAnimation)
		{
			
			if (loadingBar.color.a < 1.0f)
			{
				loadingBar.color.a += deltaTime;
				loadingFrame.color.a = loadingBar.color.a;
			}
		}

		loadingBar.widthRatio = 1 - size / (float)maxSize;
		bck.Update(deltaTime);
	}
}

void LoadSprite::Render()
{
	bck.Render(RenderInfo{D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2)});

	std::lock_guard<std::mutex> guard(lock);

	loadingFrame.Render(RenderInfo{ D3DXVECTOR2(0, -450) });
	loadingBar.Render(RenderInfo{ D3DXVECTOR2(0, -450) });
}
