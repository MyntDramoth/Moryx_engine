
struct VS_INPUT {
    float4 pos: POSITION0;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 tangent: TANGENT0;
    float3 binormal: BINORMAL0;
};

struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
};

cbuffer Constant: register(b0) {

    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    
};

VS_OUTPUT vs_main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.pos = mul(input.pos, world_space);
	output.pos = mul(output.pos, view_space);
	output.pos = mul(output.pos, projection);
	output.uv = input.uv;
	output.normal = normalize(mul(input.normal, (float3x3)world_space));
    return output;   
}

Texture2D Color: register(t0);
sampler ColorSampler: register(s0);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    
};

float4 ps_main(PS_INPUT input): SV_TARGET {
    
  return Color.Sample(ColorSampler, input.uv);

}