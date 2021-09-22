Texture2D texture;
float blinkTime;
float blinkTimer;

sampler2D InputSampler = sampler_state
{
    Texture = <texture>;
};

struct ShaderInput
{
    float2 uv : TEXCOORD0;
};

float4 main(ShaderInput input) : COLOR
{
    float4 albedo = tex2D(InputSampler, input.uv);
    
    albedo.a = blinkTimer / blinkTime;

    return albedo;
}

technique Color
{
    pass pass0
    {
         PixelShader = compile ps_2_0 main(); 
    }
}