//the names of the Texture and sampler variables HAVE TO BE THESE NAMES TO WORK!!!!!!!!!!!!!!!!!!!
Texture2D Texture: register(t0);
sampler TextureSampler : register(s0);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 camera_dir: TEXCOORD1;
};

cbuffer Constant: register(b0) {
    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    float4 light_dir;
    float4 cam_pos;
};

float4 main(PS_INPUT input): SV_TARGET {
    
    //=============
    //AMBIENT LIGHT
    //=============
    float ambient_ref = 0.2;
    float3 ambient_col = float3(1.0,1.0,1.0);

    float3 ambient_light = ambient_ref * ambient_col;

    //=============
    //DIFFUSE LIGHT
    //=============
    float diffuse_ref = 1.0;
    float3 diffuse_col = float3(1.0,1.0,1.0);
    float diffuse_light_amount = max(0.0,dot(light_dir.xyz,input.normal.xyz));

    float3 diffuse_light = diffuse_ref * diffuse_light_amount * diffuse_col;

    //==============
    //SPECULAR LIGHT
    //==============
    float spec_ref = 1.0;
    float3 spec_col = float3(1.0,1.0,1.0);
    float3 ref_light = reflect(light_dir.xyz,input.normal.xyz);
    float shine_factor = 10.0f;
    float spec_light_amount = pow(max(0.0,dot(ref_light,input.camera_dir)),shine_factor);

    float3 specular_light = spec_ref * spec_light_amount * spec_col;

    //=============
    //LIGHT PRODUCT
    //=============
    float3 final_lighting = specular_light + diffuse_light + ambient_light;

    return float4(final_lighting,1.0) * Texture.Sample(TextureSampler,input.uv * 0.5);
    //return Texture.Sample(TextureSampler,input.uv * 0.5);
}