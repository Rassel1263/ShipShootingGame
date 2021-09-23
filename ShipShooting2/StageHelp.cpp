#include "DXUT.h"
#include "StageHelp.h"

StageHelp::StageHelp(int index)
{
	prevMap.LoadAll(L"Assets/Sprites/ui/ingame/StageHelp/" + std::to_wstring(index - 1) + L".png");
	prevMap.color.a = 0.0f;
	prevMap.bCamera = false;

	curMap.LoadAll(L"Assets/Sprites/ui/ingame/StageHelp/" + std::to_wstring(index) + L".png");
	curMap.color.a = 0.0f;
	curMap.bCamera = false;

	complete.LoadAll(L"Assets/Sprites/ui/ingame/StageHelp/4.png");
	complete.color.a = 0.0f;
	complete.bCamera = false;
	

	this->index = index;
}

void StageHelp::Update(float deltaTime)
{
	if (count == 0)
	{
		if (prevMap.color.a < 1.0f)
			prevMap.color.a += deltaTime;
		else
		{
			stayTime -= deltaTime;

			if (stayTime <= 0.0f)
			{
				curMap.color.a += deltaTime;

				if (curMap.color.a >= 1.0f)
				{
					count++;
					stayTime = 1.0f;
				}
			}
		}
	}
	else if(count == 1)
	{
		stayTime -= deltaTime;

		if (stayTime <= 0.0f)
		{
			if (index < 3)
			{
				prevMap.color.a -= deltaTime;
				curMap.color.a = prevMap.color.a;

				if (prevMap.color.a <= 0.0f)
				{
					nowScene->stageStart = true;
					nowScene->player->stop = false;
					nowScene->stopTime = false;
					destroy = true;
				}
			}
			else
				count++;
		}
	}
	else if (count == 2)
	{
		complete.color.a += deltaTime;

		if (complete.color.a >= 1.0f)
		{
			auto lambda = [] {Game::GetInstance().ChangeScene(nowScene->nextScene);  };
			nowScene->obm.AddObject(new Fade(lambda));
			count++;
		}
	}
}

void StageHelp::Render()
{
	prevMap.Render(RenderInfo{});
	curMap.Render(RenderInfo{});
	complete.Render(RenderInfo{});
}
