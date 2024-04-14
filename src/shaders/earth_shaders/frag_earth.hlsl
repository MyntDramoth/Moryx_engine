//the names of the Texture and sampler variables HAVE TO BE THESE NAMES TO WORK!!!!!!!!!!!!!!!!!!!
Texture2D Texture: register(t0);
sampler TextureSampler : register(s0);

Texture2D SpecularTexture: register(t1);
sampler SpecularTextureSampler : register(s1);

Texture2D CloudTexture: register(t2);
sampler CloudTextureSampler : register(s2);

Texture2D NightTexture: register(t3);
sampler NightTextureSampler : register(s3);

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
    float time;
};

float4 main(PS_INPUT input): SV_TARGET {
    
    float4 earth_col = Texture.Sample( TextureSampler,float2(input.uv.x,1.0 - input.uv.y));
    float4 earth_spec = SpecularTexture.Sample( SpecularTextureSampler,float2(input.uv.x,1.0 - input.uv.y)).r;
    float4 cloud_col = CloudTexture.Sample(CloudTextureSampler,float2(input.uv.x,1.0 - input.uv.y) + float2(time/100.0,0.0)).r;
    float4 night_col = NightTexture.Sample(NightTextureSampler,float2(input.uv.x,1.0 - input.uv.y));

    //=============
    //AMBIENT LIGHT
    //=============
    float ambient_ref = 1.5;
    float3 ambient_col = float3(0.09,0.082,0.082);
    ambient_col *= (earth_col.rgb);
    float3 ambient_light = ambient_ref * ambient_col;

    //=============
    //DIFFUSE LIGHT
    //=============
    float diffuse_ref = 1.0;
    float3 diffuse_col_day = float3(1.0,1.0,1.0);
    diffuse_col_day *= (earth_col.rgb + cloud_col.rgb);
    float3 diffuse_col_night = float3(1.0,1.0,1.0);
    diffuse_col_night *= (night_col.rgb + cloud_col.rgb * 0.3);

    

    float diffuse_light_amount = max(0.0,dot(light_dir.xyz,input.normal.xyz));

    float3 diffuse_col = lerp(diffuse_col_night,diffuse_col_day,(diffuse_light_amount + 1.0)/2.0);

    float3 diffuse_light = diffuse_ref * diffuse_col * diffuse_light_amount;

    //==============
    //SPECULAR LIGHT
    //==============
    float spec_ref = earth_spec;
    float3 spec_col = float3(1.0,1.0,1.0);
    float3 ref_light = reflect(light_dir.xyz,input.normal.xyz);
    float shine_factor = 30.0f;
    float spec_light_amount = pow(max(0.0,dot(ref_light,input.camera_dir)),shine_factor);

    float3 specular_light = spec_ref * spec_light_amount * spec_col;

    //=============
    //LIGHT PRODUCT
    //=============
    float3 final_lighting = specular_light + diffuse_light + ambient_light;

    

    return float4(final_lighting,1.0);
    //return Texture.Sample(TextureSampler,input.uv * 0.5);
}