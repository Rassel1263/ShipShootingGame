#pragma once

template <typename T>
class Font : public ObjectUI
{
public:
	std::vector<Sprite> sprites;
	std::wstring fontName = L"";
	D3DXCOLOR* color = NULL;
	RenderInfo ri;

	T& num;
	int index = 0;
	float kerning = 0.0f;

	Font(std::wstring fontName, T& num, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float kerning, int index, int layer, D3DXCOLOR* color = NULL) : num(num)
	{
		this->fontName = fontName;
		this->pos = pos;
		ri.scale = scale;
		this->kerning = kerning;
		this->index = index;
		this->layer = layer;
		this->color = color;
	}

	virtual void Update(float deltaTime) override
	{
		WCHAR temp[256];

		wsprintf(temp, L"%02d", (int)num);

		if (index == 3)
			wsprintf(temp, L"%06d", (int)num);

		std::wstring str = temp;

		sprites.resize(str.size());
		int cnt = 0;

		for (auto s : str)
		{
			sprites[cnt].LoadAll(L"Assets/Sprites/ui/ingame/font/" + str.substr(cnt, 1) + L".png");
			sprites[cnt].bCamera = false;
			cnt++;
		}
	}

	virtual void Render() override
	{
		int size = sprites.size();

		if (index == 0)
		{
			for (int i = 0; i < size; ++i)
			{
				ri.pos = pos + D3DXVECTOR2(kerning * i, 0);
				sprites[i].Render(ri);
			}
		}
		else
		{
			for (int i = size - 1; i >= 0; --i)
			{
				ri.pos = pos + D3DXVECTOR2(-kerning * i, 0);
				sprites[size - 1 - i].Render(ri);
			}
		}
	}
};