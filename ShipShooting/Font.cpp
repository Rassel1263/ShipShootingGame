#include "Header.h"
#include "Font.h"

Font::Font(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float kerning, float& num, bool update) : num(num)
{
	this->pos = pos;
	ri.scale = scale;
	this->kerning = kerning;
	this->update = update;

	std::wstring strNum = std::to_wstring((int)num);

	int size = strNum.size();
	fonts.resize(size);

	for (int i = 0; i < size; ++i)
	{
		fonts[i].LoadAll(L"Assets/Sprites/UI/Font/Number/" + strNum.substr(i, 1) + L".png");
		fonts[i].bCamera = false;
	}
}

void Font::Update(float deltaTime)
{
	if (update)
	{
		std::wstring strNum = std::to_wstring((int)num);

		int size = strNum.size();
		fonts.resize(size);

		for (int i = 0; i < size; ++i)
			fonts[i].LoadAll(L"Assets/Sprites/UI/Font/Number/" + strNum.substr(i, 1) + L".png");
	}
}

void Font::Render()
{
	int count = 0;

	for (auto& spr : fonts)
	{
		ri.pos = pos + D3DXVECTOR2(count * kerning, 0);
		spr.Render(ri);

		count++;
	}
}
