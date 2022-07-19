struct VertexInput
{
	float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
};

cbuffer WorldBuffer : register(b0)// 0 ~ 127
{
    matrix _world;
};

cbuffer VPBuffer : register(b1)
{
    matrix _view;
    matrix _projection;
};

cbuffer ShadedBuffer : register(b0)
{
    int Selection;
}

PixelInput VS(VertexInput input)
{
	PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
    
	output.uv = input.uv;
	return output;
}

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, input.uv);
    
	float3 greyscale = { 0.89f, 0.2f, 0.3f };


	//lerp ���� �����Լ� (���� �ϰ���� �ȼ��� rgb��, ��� rgb��, ����)
	greyscale = lerp(greyscale, color , 1-((float)Selection/100.0f));

	
    return float4(greyscale, 1);
}