#include "DXUT.h"
#include "MsgBox.h"

MsgBox::MsgBox()
{
	for (int i = 0; i < 2; ++i)
	{
		spr[i].LoadAll(L"Assets/Sprites/ui/ingame/messagebox.png");
		spr[i].color.a = 0.0f;
		spr[i].bCamera = false;
	}
}

void MsgBox::Update(float deltaTime)
{
	for(int i = 0; i < 2; ++i)
		MessageUpdate(deltaTime, i);
}

void MsgBox::Render()
{
	if (msgInfo[0].spawnMsg)
	{
		spr[0].Render(RenderInfo{D3DXVECTOR2(800, -20)});
		msgBox[0].Render(RenderInfo{D3DXVECTOR2(670, 60)});
	}
	
	if (msgInfo[1].spawnMsg)
	{
		spr[1].Render(RenderInfo{ D3DXVECTOR2(800, 100) });
		msgBox[1].Render(RenderInfo{ D3DXVECTOR2(670, 160) });
	}
}

void MsgBox::SpawnMsgBox(std::wstring message)
{
	if (msgInfo[0].spawnMsg) return;

	msgInfo[0].spawnMsg = true;
	msgBox[0].LoadAll(L"Assets/Sprites/ui/ingame/Message/" + message + L".png");
	msgBox[0].color.a = 0.0f;
	msgBox[0].bCamera = false;
}

void MsgBox::SpawnMsgBox2(std::wstring message)
{
	if (msgInfo[1].spawnMsg) return;

	msgInfo[1].spawnMsg = true;
	msgBox[1].LoadAll(L"Assets/Sprites/ui/ingame/Message/" + message + L".png");
	msgBox[1].color.a = 0.0f;
	msgBox[1].bCamera = false;
}

void MsgBox::MessageUpdate(float deltaTime, int i)
{
	if (msgInfo[i].spawnMsg)
	{
		spr[i].color.a += deltaTime * msgInfo[i].destColor;

		if (spr[i].color.a >= 1.0f)
		{
			msgInfo[i].msgTime += deltaTime;

			if (msgInfo[i].msgTime > 1.0f && !msgInfo[i].closeMsg)
			{
				msgInfo[i].closeMsg = true;
				msgInfo[i].destColor = -msgInfo[i].destColor;
			}
		}

		if (spr[i].color.a <= 0.0f)
		{
			msgInfo[i].spawnMsg = false;
			msgInfo[i].closeMsg = false;
			msgInfo[i].destColor = 1.0f;
			msgInfo[i].msgTime = 0.0f;
		}

		msgBox[i].color.a = spr[i].color.a;
		std::clamp(spr[i].color.a, 0.0f, 1.0f);
	}
}
