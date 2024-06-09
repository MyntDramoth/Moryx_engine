
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

Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    
};

float4 ps_main(PS_INPUT input): SV_TARGET {
    
    
   	float4 texture_col = Texture.Sample( TextureSampler,float2(input.uv.x,1.0 - input.uv.y));

    //=============
    //AMBIENT LIGHT
    //=============
    float ambient_ref = 8.5;
    float3 ambient_col = float3(0.09,0.082,0.082);
    ambient_col *= (texture_col.rgb);

    float3 ambient_light = ambient_ref * ambient_col;


    //=============
    //DIFFUSE LIGHT
    //=============

    float3 light_direction = normalize(float3(-1, 1, 1));

    float diffuse_ref = 0.7;
    float diffuse_light_amount = max(dot(light_direction.xyz,input.normal.xyz), 0.0);
	float3 diffuse_col = float3(1.0,1.0,1.0);
    diffuse_col *= (texture_col.rgb);
    
    float3 diffuse_light = (diffuse_ref * diffuse_col * diffuse_light_amount);

    //==============
    //SPECULAR LIGHT
    //==============
    // float spec_ref = 0.0f;
    // float3 spec_col = float3(1.0,1.0,1.0);
    // float3 ref_light = reflect(light_dir_point.xyz,input.normal.xyz);
    // float shine_factor = 30.0f;
    // //float spec_light_amount = pow(max(0.0,dot(ref_light,camera_dir)),shine_factor);

    // float3 specular_light = (spec_ref * /*spec_light_amount */ spec_col);

    //=============
    //LIGHT PRODUCT
    //=============
    float3 final_lighting = /*specular_light +*/ diffuse_light + ambient_light;

    return float4(final_lighting,1.0);
    //return Texture.Sample(TextureSampler,input.uv * 0.5);
}