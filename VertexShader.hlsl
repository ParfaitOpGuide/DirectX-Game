struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};


cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

VS_OUTPUT vsmain( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
   //output.position = lerp(input.position, input.position1, (sin(m_time / 1000.0f) + 1.f) / 2.f);
    //world space
    output.position = mul(input.position, m_world);
    //view space
    output.position = mul(output.position, m_view);
    //screen space
    output.position = mul(output.position, m_proj);
    
    
    output.color = input.color;
    output.color1 = input.color1;

	return output;
}