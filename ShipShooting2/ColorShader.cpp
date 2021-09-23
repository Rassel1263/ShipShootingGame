#include "DXUT.h"
#include "ColorShader.h"

ColorShader::ColorShader()
{
    shader = ShaderManager::GetInstance().GetEffect("Color");
}

ColorShader::~ColorShader()
{
    SAFE_RELEASE(shader);
}

HRESULT ColorShader::Prepare()
{
    return shader->SetTechnique(shader->GetTechniqueByName("Color"));
}

HRESULT ColorShader::Begin()
{
    if(FAILED(shader->Begin(NULL, 0)))
        return E_FAIL;

    return shader->BeginPass(0);
}

HRESULT ColorShader::End()
{
    return shader->End();
}

HRESULT ColorShader::SetTexture(const Texture* texture)
{
    if(FAILED(shader->SetTexture(shader->GetParameterByName(0, "spriteTexture"), texture->src)))
        return E_FAIL;
}

HRESULT ColorShader::SetColor(D3DXVECTOR4 color, bool plus)
{
    if(FAILED(shader->SetVector(shader->GetParameterByName(0, "color"), &color)))
        return E_FAIL;
    
    if(FAILED(shader->SetBool(shader->GetParameterByName(0,"plus"), plus)))
        return E_FAIL;
}

void ColorShader::Render(ColorShader* shader, Sprite& sprite, RenderInfo& ri, D3DXVECTOR4 color, bool plus)
{
    shader->Prepare();
    shader->SetTexture(sprite.GetNowScene());
    shader->SetColor(color, plus);
    shader->Begin();
    sprite.Render(ri);
    shader->End();

}
