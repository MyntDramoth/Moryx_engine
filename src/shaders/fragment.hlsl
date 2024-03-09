//the names of the Texture and sampler variables HAVE TO BE THESE NAMES TO WORK!!!!!!!!!!!!!!!!!!!
Texture2D Texture: register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD0;
};

cbuffer Constant: register(b0) {
    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    unsigned int time;
};

float4 main(PS_INPUT input): SV_TARGET {
    //return float4(1.0f,1.0f,1.0f,1.0f);
    return Texture.Sample(TextureSampler,input.uv);
}