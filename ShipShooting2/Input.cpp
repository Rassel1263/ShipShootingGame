#include "DXUT.h"
#include "Input.h"

void Input::Start()
{
	memset(curKey, 0, sizeof(curKey));
	memset(oldKey, 0, sizeof(oldKey));
	memset(keyMap, 0, sizeof(keyMap));

	SetKeyboardState(curKey);
}

void Input::Update()
{
	memcpy(oldKey, curKey, sizeof(oldKey));

	memset(curKey, 0, sizeof(curKey));
	memset(keyMap, 0, sizeof(keyMap));

	GetKeyboardState(curKey);

	for (int i = 0; i < 256; ++i)
	{
		BYTE key = curKey[i] & 0x80;
		curKey[i] = (key) ? 1 : 0;

		int old = oldKey[i];
		int cur = curKey[i];

		if (old == 0 && cur == 1) keyMap[i] = InputState::INPUT_DOWN;
		else if (old == 1 && cur == 0) keyMap[i] = InputState::INPUT_UP;
		else if (old == 1 && cur == 1) keyMap[i] = InputState::INPUT_PRESS;
		else keyMap[i] = InputState::INPUT_NONE;
	}

	mWorldPos = D3DXVECTOR2(mousePos.x - 960, -mousePos.y + 540);
}

bool Input::KeyDown(int key)
{
	return keyMap[key] == InputState::INPUT_DOWN;
}

bool Input::KeyUp(int key)
{
	return keyMap[key] == InputState::INPUT_UP;
}

bool Input::KeyPress(int key)
{
	return keyMap[key] == InputState::INPUT_PRESS;
}
