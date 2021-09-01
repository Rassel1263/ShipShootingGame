#include "Header.h"
#include "ColorShader.h"

ColorShader::ColorShader()
{
    shader = ShaderManager::GetInstance().GetEffect("Color");
}

ColorShader::~ColorShader()
{
    shader = NULL;
}

HRESULT ColorShader::Prepare()
{
    return shader->SetTechnique(shader->GetTechniqueByName("Outline"));
}

HRESULT ColorShader::Begin()
{
    if (FAILED(shader->Begin(NULL, 0)))
        return E_FAIL;

    return shader->BeginPass(0);
}

HRESULT ColorShader::End()
{
    return shader->End();
}

HRESULT ColorShader::SetTexture(const Texture* texture)
{
    if (FAILED(shader->SetTexture(shader->GetParameterByName(0, "SpriteTexture"), texture->src)))
        return E_FAIL;
}

HRESULT ColorShader::SetColor(D3DXVECTOR4 color)
{
    if (FAILED(shader->SetVector(shader->GetParameterByName(0, "color"), &color)))
        return E_FAIL;
}

void ColorShader::Render(ColorShader* shaderManager, Sprite& sprite, RenderInfo& ri, D3DXVECTOR4 color)
{
    shaderManager->Prepare();
    shaderManager->SetTexture(sprite.GetNowScene());
    shaderManager->SetColor(color);
    shaderManager->Begin();
    sprite.Render(ri);
    shaderManager->End();
}
