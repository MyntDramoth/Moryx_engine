
struct VS_INPUT {
    float4 pos: POSITION0;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 tangent: TANGENT0;
    float3 binormal: BINORMAL0;
    float4 pos_inst: POSITION1; // Tile World Position
    float2 uv_inst: TEXCOORD1; // Offset/position in the texture atlas
    float2 offset: TEXCOORD2; // Scale (size) in the texture atlas
};


struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD2;
};


cbuffer Constant: register(b0) {

    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    float4 camera_position;
};

VS_OUTPUT vs_main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.pos = mul(input.pos + input.pos_inst, world_space);
	output.pos = mul(output.pos, view_space);
	output.pos = mul(output.pos, projection);
	
    float2 atlas_uv = ((input.uv * input.uv_inst) + input.offset);
    
    output.uv = atlas_uv;
    return output;   
}

Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD2;
};

float4 ps_main(PS_INPUT input): SV_TARGET {
    
    
   	float4 texture_col = Texture.Sample( TextureSampler, float2(input.uv.x,1.0 - input.uv.y));

    //=============
    //AMBIENT LIGHT
    //=============
    float ambient_ref = 8.5;
    float3 ambient_col = float3(0.09,0.082,0.082);
    ambient_col *= (texture_col.rgb);

    float3 ambient_light = ambient_ref * ambient_col;

    //=============
    //LIGHT PRODUCT
    //=============
    float3 final_lighting = ambient_light;

    return float4(final_lighting,1.0);
    
}