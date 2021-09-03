#include "Header.h"
#include "YouDie.h"

YouDie::YouDie()
{
	Game::GetInstance().timeScale = 0.0f;

	spr.LoadAll(L"Assets/Sprites/UI/youdie.png");
	spr.bCamera = false;
	spr.color.a = 0.0f;

	layer = 20;
}

void YouDie::Update(float deltaTime)
{
	if (spr.color.a < 1.0f)
		spr.color.a += Game::GetInstance().unScaleTime;
	else
	{
		if (Input::GetInstance().KeyDown(VK_RETURN))
		{
			Game::GetInstance().timeScale = 1.0f;
			Game::GetInstance().ChangeScene(new MainScene());
		}
	}
}

void YouDie::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
