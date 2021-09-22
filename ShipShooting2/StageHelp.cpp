#include "DXUT.h"
#include "StageHelp.h"

StageHelp::StageHelp()
{
	prevMap.LoadAll(L"Assets/Sprites/ui/ingame/StageHelp/" + std::to_wstring(nowScene->curStage - 1) + L".png");
	prevMap.color.a = 0.0f;
	prevMap.bCamera = false;

	curMap.LoadAll(L"Assets/Sprites/ui/ingame/StageHelp/" + std::to_wstring(nowScene->curStage) + L".png");
	curMap.color.a = 0.0f;
	curMap.bCamera = false;
}

void StageHelp::Update(float deltaTime)
{
	if (draw)
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
					draw = false;
					stayTime = 1.0f;
				}
			}
		}
	}
	else
	{
		stayTime -= deltaTime;

		if (stayTime <= 0.0f)
		{
			prevMap.color.a -= deltaTime;
			curMap.color.a = prevMap.color.a;

			if (prevMap.color.a <= 0.0f)
			{
				destroy = true;
				nowScene->stageStart = true;
				nowScene->player->stop = false;
				nowScene->stopTime = false;
			}
		}
	}
}

void StageHelp::Render()
{
	prevMap.Render(RenderInfo{});
	curMap.Render(RenderInfo{});
}
