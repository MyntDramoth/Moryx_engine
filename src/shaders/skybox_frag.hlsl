//the names of the Texture and sampler variables HAVE TO BE THESE NAMES TO WORK!!!!!!!!!!!!!!!!!!!
Texture2D Texture: register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 camera_dir: TEXCOORD1;
};


float4 main(PS_INPUT input): SV_TARGET {
    
    return Texture.Sample(TextureSampler,1.0 - input.uv);
}