#pragma once

enum class InputState
{
	INPUT_NONE,
	INPUT_DOWN,
	INPUT_UP,
	INPUT_PRESS
};

class Input : public Singleton<Input>
{
protected:
	BYTE m_KeyCur[256];
	BYTE m_KeyOld[256];
	InputState m_KeyMap[256];


public:
	D3DXVECTOR2 mousePos = { 0, 0 };
	
	void Start();
	int Update();

	bool KeyDown(int nKey);
	bool KeyUp(int nKey);
	bool KeyPress(int nKey);
	D3DXVECTOR2 GetFixedMousePos();
};

