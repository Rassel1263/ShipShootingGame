#include "DXUT.h"
#include "StageFont.h"

StageFont::StageFont(Type type)
{
	this->type = type;

	bck.LoadAll(L"Assets/Sprites/black.png");
	if (type == Type::START)
	{
		spr.LoadAll(L"Assets/Sprites/message/stageStart/" + std::to_wstring(nowScene->curStage), 0.03f, false);
		bck.color.a = 1.0f;
		Game::GetInstance().timeScale = 0.0f;
	}
	if (type == Type::CLEAR)
	{
		spr.LoadAll(L"Assets/Sprites/message/stageClear/", 0.05f, false);
		bck.color.a = 1.0f;
	}
	else if (type == Type::FAIL)
	{
		spr.LoadAll(L"Assets/Sprites/message/GameOver", 0.03f, false);
		bck.color.a = 0.0f;
	}

	spr.bCamera = false;
	bck.bCamera = false;

	layer = 2;
}

void StageFont::Update(float deltaTime)
{
	deltaTime = Game::GetInstance().unscaleTime;

	if (type == Type::START)
	{
		if (!spr.bAnimation)
		{
			bck.color.a -= deltaTime * 2;

			if (bck.color.a <= 0.0f)
			{
				destroy = true;
				Game::GetInstance().timeScale = 1.0f;
				nowScene->obm.AddObject(new StageHelp(nowScene->curStage));
			}
		}
	}
	else if (type == Type::CLEAR)
	{
		if (!spr.bAnimation)
		{
			nowScene->obm.AddObject(new CalcPage());
			destroy = true;
		}
	}

	else if (type == Type::FAIL)
	{
		if (!spr.bAnimation)
		{
			bck.color.a += deltaTime * 0.5f;
			spr.color.a -= deltaTime * 0.5f;

			if (bck.color.a >= 1.0f)
			{
				Game::GetInstance().timeScale = 1.0f;
				Game::GetInstance().ChangeScene(new MainScene());
			}
		}
	}

	spr.Update(deltaTime);
}

void StageFont::Render()
{
	if (type != Type::CLEAR)
		bck.Render(RenderInfo{});

	ri.pos = pos;
	spr.Render(ri);
}
