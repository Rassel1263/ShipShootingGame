#pragma once
class ColorShader
{
private:
	LPD3DXEFFECT shader = NULL;

public:
	ColorShader();
	virtual ~ColorShader();

public:
	HRESULT Prepare();
	HRESULT Begin();
	HRESULT End();

	HRESULT SetTexture(const Texture* texture);
	HRESULT SetColor(D3DXVECTOR4 color);

	void Render(ColorShader* shaderManager, Sprite& sprite, RenderInfo& ri, D3DXVECTOR4 color = { 1, 1, 1 ,1 });
};

