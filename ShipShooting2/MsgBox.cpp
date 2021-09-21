#include "DXUT.h"
#include "MsgBox.h"

MsgBox::MsgBox()
{
	spr.LoadAll(L"Assets/Sprites/ui/ingame/messagebox.png");
	spr.color.a = 0.0f;
	spr.bCamera = false;
}

void MsgBox::Update(float deltaTime)
{
	if (spawnMsg)
	{
		spr.color.a += deltaTime * destColor;

		if (spr.color.a >= 1.0f)
		{
			msgTime += deltaTime;

			if (msgTime > 1.0f && !closeMsg)
			{
				closeMsg = true;
				destColor = -destColor;
			}
		}

		if (spr.color.a <= 0.0f)
		{
			spawnMsg = false;
			closeMsg = false;
			destColor = 1.0f;
			msgTime = 0.0f;
		}

		msgBox.color.a = spr.color.a;
		std::clamp(spr.color.a, 0.0f, 1.0f);
	}

}

void MsgBox::Render()
{
	if (spawnMsg)
	{
		spr.Render(RenderInfo{D3DXVECTOR2(800, -20)});
		msgBox.Render(RenderInfo{D3DXVECTOR2(670, 60)});
	}
}

void MsgBox::SpawnMsgBox(std::wstring message)
{
	if (spawnMsg) return;

	spawnMsg = true;
	msgBox.LoadAll(L"Assets/Sprites/ui/ingame/Message/" + message + L".png");
	msgBox.color.a = 0.0f;
	msgBox.bCamera = false;
}
