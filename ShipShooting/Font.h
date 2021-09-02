#pragma once

template <typename T>
class Font : public Object
{
public:
    std::vector<Sprite> sprites;
    std::wstring fontName = L"";
    RenderInfo ri;
    T& num;
    int scoreNum = 0;
    float kerning = 0.0f;

    Font(std::wstring fontName, T & num, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float kerning, int scoreNum, int layer = 10)
        : num(num)
    {
        this->fontName = fontName;
        this->pos = pos;
        this->layer = layer;
        this->ri.scale = scale;
        this->kerning = kerning;
        this->scoreNum = scoreNum;

        layer = 10;
    }

    virtual void Update(float deltaTime) override
    {
        WCHAR temp[10];

        wsprintf(temp, L"%02d", (int)num);

        if (scoreNum == 3)
            wsprintf(temp, L"%06d", (int)num);

        std::wstring str = temp;

        sprites.resize(str.size());
        int count = 0;

        for (auto s : str)
        {
            sprites[count].LoadAll(L"Assets/Sprites/UI/Font/" + fontName + std::to_wstring(s - '0') + L".png");
            sprites[count].bCamera = false;
            count++;
        }
    }

    virtual void Render() override
    {
        int size = sprites.size();

        if (scoreNum == 0)
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