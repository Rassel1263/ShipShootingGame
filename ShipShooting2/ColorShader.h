#pragma once
class ColorShader
{
private:
	LPD3DXEFFECT shader = NULL;
public:
	ColorShader();
	~ColorShader();

public:
	HRESULT Prepare();
	HRESULT Begin();
	HRESULT End();
	HRESULT SetTexture(const Texture* texture);
	HRESULT SetColor(D3DXVECTOR4 color, bool plus);

	void Render(ColorShader* shader, Sprite& sprite, RenderInfo& ri, D3DXVECTOR4 color = { 1, 1, 1, 1 }, bool plus = false);
};

