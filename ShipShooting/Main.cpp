#include "Header.h"
#include "Main.h"
#include "Help.h"
#include "Rank.h"

Main::Main()
{
	bck.LoadAll(L"Assets/Sprites/Main/bck.png");

	button.resize(4);
	
	button[0].LoadAll(L"Assets/Sprites/Main/START");
	button[1].LoadAll(L"Assets/Sprites/Main/HELP");
	button[2].LoadAll(L"Assets/Sprites/Main/RANK");
	button[3].LoadAll(L"Assets/Sprites/Main/EXIT");

	button[0].scene = 1;
}

void Main::Update(float deltaTime)
{
	auto& input = static_cast<MainScene*>(nowScene)->input;
	if (!input) return;

	int prevNum = cNum;

	if (Input::GetInstance().KeyDown(VK_UP))
		if (cNum > 0) cNum--;

	if (Input::GetInstance().KeyDown(VK_DOWN))
		if(cNum < 3) cNum++;

	if (prevNum != cNum)
	{
		button[prevNum].scene = 0;
		button[cNum].scene = 1;
	}

	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		input = false;

		switch (cNum)
		{
		case 0:
			Game::GetInstance().ChangeScene(new GameScene());
			break;
		case 1:
			nowScene->obm.AddObject(new Help());
			break;
		case 2:
			nowScene->obm.AddObject(new Rank());
			break;
		case 3:
			PostQuitMessage(0);
			break;
		}
	}

}

void Main::Render()
{
	bck.Render(RenderInfo{});


	for (int i = 0; i < 4; ++i)
		button[i].Render(RenderInfo{ D3DXVECTOR2(0, 50 + i * -120) });
}
