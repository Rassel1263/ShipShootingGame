#include "DXUT.h"
#include "Main.h"

Main::Main()
{
	Camera::GetInstance().destCameraPos = { 0,0 };
	Camera::GetInstance().cameraPos = { 0, 0 };

	ui.resize(8);
	
	std::wstring filePath = L"Assets/Sprites/ui/outgame/Menu/";
	fadeSpr.LoadAll(L"Assets/Sprites/black.png");
	fadeSpr.color.a = 0.0f;

	ui[0].LoadAll(filePath + L"background");
	ui[1].LoadAll(filePath + L"deco.png");
	ui[2].LoadAll(filePath + L"mainlogo.png");
	ui[3].LoadAll(filePath + L"gamestart.png");
	ui[4].LoadAll(filePath + L"gamerank.png");
	ui[5].LoadAll(filePath + L"gamehelp.png");
	ui[6].LoadAll(filePath + L"gameexit.png");
	ui[7].LoadAll(filePath + L"menuselect.png");

}

void Main::Update(float deltaTime)
{
	ChoiceBtn();

	if(alpha < 1.0f)
		alpha += deltaTime;

	for (int i = 1; i < 8; ++i)
	{
		ui[i].color.a = alpha;
	}

	if (Input::GetInstance().KeyDown(VK_RETURN) && !static_cast<MainScene*>(nowScene)->input)
	{
		static_cast<MainScene*>(nowScene)->input = true;
		SoundManager::GetInstance().Play(L"clickBtn");

		switch (cNum)
		{
		case 0:
			fade = true;
			break;
		case 1:
			nowScene->obm.AddObject(new Rank());
			break;
		case 2:
			nowScene->obm.AddObject(new Help());
			break;
		case 3:
			fade = true;
			break;
		}
	}


	if (fade)
	{
		fadeSpr.color.a += deltaTime;

		if (fadeSpr.color.a >= 1.0f)
		{
			if (cNum == 0)
				Game::GetInstance().ChangeScene(new GameScene());
			else
				PostQuitMessage(0);
		}
	}


	ui[0].Update(deltaTime);
}

void Main::Render()
{
	for (int i = 0; i < 8; ++i)
	{
		if (i < 3)
			ui[i].Render(RenderInfo{});
		else if (i < 7)
			ui[i].Render(RenderInfo{D3DXVECTOR2(0, 200 - i * 100)});
		else 
			ui[i].Render(RenderInfo{ D3DXVECTOR2(25, -100 - cNum * 100)});
	}

	fadeSpr.Render(RenderInfo{});
}

void Main::ChoiceBtn()
{
	if (static_cast<MainScene*>(nowScene)->input) return;

	pNum = cNum;

	if (Input::GetInstance().KeyDown(VK_DOWN))
		cNum++;

	if (Input::GetInstance().KeyDown(VK_UP))
		cNum--;

	cNum = std::clamp(cNum, 0, 3);

	if (cNum != pNum)
		SoundManager::GetInstance().Play(L"moveBtn");
}
