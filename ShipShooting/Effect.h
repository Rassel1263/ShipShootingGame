#pragma once
class Effect : public Object
{
public:
	Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, std::function<void()> func = 0) {};
};

