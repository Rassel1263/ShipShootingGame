Texture2D spriteTexture;
float4 color;
bool plus;

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
    
    if (albedo.a >= 0.8 || albedo.r >= 0.5)
    {
        if (plus)
            albedo += color;
        else
            albedo = color;
    }
    
    return albedo;
}

technique Color
{
    pass pass0
    {
        PixelShader = compile ps_2_0 main();
    }
}