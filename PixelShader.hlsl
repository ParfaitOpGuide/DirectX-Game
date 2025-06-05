struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};

Texture2D tex : register(t0);
SamplerState texsampler : register(s0);

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
     float4 diffuse_texture = tex.Sample(texsampler, input.texcoord);
    return diffuse_texture;
}