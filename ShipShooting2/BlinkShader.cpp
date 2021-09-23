#include "DXUT.h"
#include "BlinkShader.h"

BlinkShader::BlinkShader()
{
    shader = ShaderManager::GetInstance().GetEffect("Blink");
}

BlinkShader::~BlinkShader()
{
    SAFE_RELEASE(shader);
}

HRESULT BlinkShader::Prepare()
{
    return shader->SetTechnique(shader->GetTechniqueByName("Blink"));
}

HRESULT BlinkShader::Begin()
{
    if (FAILED(shader->Begin(NULL, 0)))
        return E_FAIL;

    return shader->BeginPass(0);
}

HRESULT BlinkShader::End()
{
    return shader->End();
}

HRESULT BlinkShader::SetTexture(const Texture* texture)
{
    if (FAILED(shader->SetTexture(shader->GetParameterByName(0, "spriteTexture"), texture->src)))
        return E_FAIL;
}

HRESULT BlinkShader::SetTime(float timer, float time)
{
    if (FAILED(shader->SetFloat(shader->GetParameterByName(0, "blinkTimer"), timer)))
        return E_FAIL;

    if (FAILED(shader->SetFloat(shader->GetParameterByName(0, "blinkTime"), time)))
        return E_FAIL;
}

void BlinkShader::Render(BlinkShader* shader, Sprite& sprite, RenderInfo& ri, float timer, float time)
{
    shader->Prepare();
    shader->SetTexture(sprite.GetNowScene());
    shader->SetTime(timer, time);
    shader->Begin();
    sprite.Render(ri);
    shader->End();
}
