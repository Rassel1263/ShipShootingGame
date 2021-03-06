#pragma once

enum class InputState
{
	INPUT_NONE,
	INPUT_DOWN,
	INPUT_UP,
	INPUT_PRESS,
};

class Input : public Singleton<Input>
{
protected:
	BYTE curKey[256];
	BYTE oldKey[256];
	InputState keyMap[256];

public:
	D3DXVECTOR2 mousePos = { 0, 0 };
	D3DXVECTOR2 mWorldPos= { 0, 0 };

	void Start();
	void Update();

	bool KeyDown(int key);
	bool KeyUp(int key);
	bool KeyPress(int key);

};

