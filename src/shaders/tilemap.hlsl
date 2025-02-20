
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
    uint depth: TEXCOORD3;
};


cbuffer Constant: register(b0) {

    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    float4 camera_position;
};

VS_OUTPUT vs_main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
     float true_y = input.pos_inst.y;

    float scaleFactor = 1.0 + (true_y * 0.1); // Increase scale with height
    
    // Scale the X and Y values
    float y_offset = (scaleFactor - 1.0) * 0.5;
    float4 scaledPos = float4((input.pos.x - y_offset*50) * scaleFactor,input.pos.y,(input.pos.z - y_offset*25) * scaleFactor ,input.pos.w);
  
    input.pos_inst.xz *= scaleFactor;
    
    
    output.pos = mul(scaledPos + input.pos_inst, world_space);
    output.pos.y += true_y;
	output.pos = mul(output.pos, view_space);
	output.pos = mul(output.pos, projection);
	
    float2 atlas_uv = ((input.uv * input.uv_inst) + input.offset);
    output.depth = input.pos_inst.y;
    output.uv = atlas_uv;
    return output;   
}

Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD2;
    uint depth: TEXCOORD3;
};

float4 ps_main(PS_INPUT input): SV_TARGET {
    
    
   	float4 texture_col = Texture.Sample( TextureSampler, float2(input.uv.x,1.0 - input.uv.y));

    //=============
    //AMBIENT LIGHT
    //=============
    float ambient_ref = 8.5;
    //float3 ambient_col = float3(0.09,0.082,0.082);
    //float3 ambient_col = float3(0.09,0.09,0.09);
    float col_mult = 0.09f;
    float3 ambient_col = float3(col_mult,col_mult,col_mult);
    ambient_col *= (texture_col.rgb);
    float depth = input.depth/10.0f;
    
    float depth_col = 1-(depth);
    ambient_col =  lerp(col_mult,ambient_col,depth_col+1.0f);

    float3 ambient_light = ambient_ref * ambient_col;

    //=============
    //LIGHT PRODUCT
    //=============
    float3 final_lighting = ambient_light;

    return float4(final_lighting,1.0);
    
}