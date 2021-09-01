Texture2D SpriteTexture;
float4 color;

sampler2D InputSampler = sampler_state
{
    Texture = <SpriteTexture>;
};

struct ShaderOuput
{
    float2 uv : TEXCOORD0;
};

float4 main(ShaderOuput input) : COLOR
{
    float4 albedo = tex2D(InputSampler, input.uv);
    
    if (albedo.a != 0)
    {
        albedo.rgb += color.rgb;
    }
    
        return float4(albedo);
}

technique Outline
{
    pass pass0
    {
        PixelShader = compile ps_2_0 main();
    }
}