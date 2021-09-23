Texture2D spriteTexture;
float blinkTime = 0.0f;
float blinkTimer = 0.0f;

sampler2D InputSampler = sampler_state
{
    Texture = <spriteTexture>;
};

struct ShaderInput
{
    float2 uv : TEXCOORD0;
};

float4 main(ShaderInput input) : COLOR
{
    float4 albedo = tex2D(InputSampler, input.uv);
    
    if (albedo.a >= 0.8)
        albedo.a = 1 - (blinkTimer / blinkTime);

    return albedo;
}

technique Blink
{
    pass pass0
    {
         PixelShader = compile ps_2_0 main(); 
    }
}