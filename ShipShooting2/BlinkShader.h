#pragma once
class BlinkShader
{
private:
	LPD3DXEFFECT shader = NULL;
public:
	BlinkShader();
	~BlinkShader();

public:
	HRESULT Prepare();
	HRESULT Begin();
	HRESULT End();
	HRESULT SetTexture(const Texture* texture);
	HRESULT SetTime(float timer, float time);

	void Render(BlinkShader* shader, Sprite& sprite, RenderInfo& ri, float timer, float time);
};

