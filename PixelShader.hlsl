Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};


cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
   // return float4(lerp(input.color, input.color1, (sin(m_time / 1000.f) + 1.f) / 2.f), 1.0f);
   //return float4(input.color, 1.0f);
    return Texture.Sample(TextureSampler, input.texcoord);
}