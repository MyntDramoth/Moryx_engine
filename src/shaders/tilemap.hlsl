
struct VS_INPUT {
    float4 pos: POSITION0;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 tangent: TANGENT0;
    float3 binormal: BINORMAL0;
    float4 pos_inst: POSITION1; // Tile World Position
    float2 uv_inst: TEXCOORD1; // Offset/position in the texture atlas
    float2 offset: TEXCOORD2; // Scale (size) in the texture atlas
    float2 decal_uv: TEXCOORD3;

    uint edge_mask: COLOR0;
};


struct VS_OUTPUT {
    float4 pos_inst: POSITION1;
    //float2 uv_inst: TEXCOORD0;
    uint edge_mask: COLOR0;

    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD0;
    float2 decal_uv: TEXCOORD1;
    float3 normal: NORMAL0;
    float3 camera_dir: TEXCOORD2;
    uint depth: TEXCOORD3;

    float2 t_edge_offset: TEXCOORD4;
    float2 r_edge_offset: TEXCOORD5;
    float2 l_edge_offset: TEXCOORD6;
    float2 b_edge_offset: TEXCOORD7;

    float2 t_shadow_offset: TEXCOORD8;
    float2 r_shadow_offset: TEXCOORD9;
    float2 l_shadow_offset: TEXCOORD10;
    float2 b_shadow_offset: TEXCOORD11;
};



cbuffer Constant: register(b0) {

    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    float4 camera_position;
    float2 t_edge_offset;
    float2 r_edge_offset;
    float2 l_edge_offset;
    float2 b_edge_offset;

    float2 t_shadow_offset;
    float2 r_shadow_offset;
    float2 l_shadow_offset;
    float2 b_shadow_offset;
    
};

VS_OUTPUT vs_main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    float true_y = input.pos_inst.y;

    float scaleFactor = 1.0 /*+ (true_y * 0.1)*/; // Increase scale with height
    
    // Scale the X and Y values
    float y_offset = (scaleFactor - 1.0) * 0.5;
    //float4 scaledPos = float4((input.pos.x - y_offset*50) * scaleFactor,input.pos.y,(input.pos.z - y_offset*25) * scaleFactor ,input.pos.w);
    float4 scaledPos = float4((input.pos.x),input.pos.y,(input.pos.z) ,input.pos.w);
  
    input.pos_inst.xz *= scaleFactor;
    float4 pos_inst = float4(input.pos_inst.x,1.0f,input.pos_inst.z, input.pos_inst.w);

    output.pos = mul(scaledPos + pos_inst, world_space);
    if(true_y > 0.0f) {
        output.pos.y += true_y;
    }
	output.pos = mul(output.pos, view_space);
	output.pos = mul(output.pos, projection);
	
    float2 atlas_uv = ((input.uv * input.uv_inst) + input.offset);
    float2 atl_decal_uv = ((input.uv * input.uv_inst) - input.decal_uv);

    output.depth = input.pos_inst.y;

    output.uv = saturate(atlas_uv);
    output.decal_uv = saturate(atl_decal_uv);

    output.t_edge_offset = float2((input.uv * input.uv_inst) - t_edge_offset);
    output.r_edge_offset = float2((input.uv * input.uv_inst) - r_edge_offset);
    output.l_edge_offset = float2((input.uv * input.uv_inst) - l_edge_offset);
    output.b_edge_offset = float2((input.uv * input.uv_inst) - b_edge_offset);

    output.t_shadow_offset = float2((input.uv * input.uv_inst) - t_shadow_offset);
    output.r_shadow_offset = float2((input.uv * input.uv_inst) - r_shadow_offset);
    output.l_shadow_offset = float2((input.uv * input.uv_inst) - l_shadow_offset);
    output.b_shadow_offset = float2((input.uv * input.uv_inst) - b_shadow_offset);
    


    //output.edge_uv = (input.uv * input.uv_inst);
    output.edge_mask = input.edge_mask;
    
    return output;   
}

struct PS_INPUT {
    float4 pos_inst: POSITION1;
    //float2 uv_inst: TEXCOORD0;
    uint edge_mask: COLOR0;

    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD0;
    float2 decal_uv: TEXCOORD1;
    float3 normal: NORMAL0;
    float3 camera_dir: TEXCOORD2;
    uint depth: TEXCOORD3;

    float2 t_edge_offset: TEXCOORD4;
    float2 r_edge_offset: TEXCOORD5;
    float2 l_edge_offset: TEXCOORD6;
    float2 b_edge_offset: TEXCOORD7;

    float2 t_shadow_offset: TEXCOORD8;
    float2 r_shadow_offset: TEXCOORD9;
    float2 l_shadow_offset: TEXCOORD10;
    float2 b_shadow_offset: TEXCOORD11;
    
};

Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

Texture2D Decal: register(t1);
sampler DecalSampler: register(s1);

float4 ps_main(PS_INPUT input): SV_TARGET {

    
   	float4 texture_col = Texture.Sample( TextureSampler, float2(input.uv.x, 1-input.uv.y));
    float4 decal_tex = Decal.Sample(TextureSampler,  float2(input.decal_uv.x, 1-input.decal_uv.y));

    float4 t_edge_tex = Decal.Sample(DecalSampler,  float2(input.t_edge_offset.x, 1-input.t_edge_offset.y));
    float4 r_edge_tex = Decal.Sample(DecalSampler,  float2(input.r_edge_offset.x, 1-input.r_edge_offset.y));
    float4 l_edge_tex = Decal.Sample(DecalSampler,  float2(input.l_edge_offset.x, 1-input.l_edge_offset.y));
    float4 b_edge_tex = Decal.Sample(DecalSampler,  float2(input.b_edge_offset.x, 1-input.b_edge_offset.y));

    float4 t_shadow_tex = Decal.Sample(DecalSampler,  float2(input.t_shadow_offset.x, 1-input.t_shadow_offset.y));
    float4 r_shadow_tex = Decal.Sample(DecalSampler,  float2(input.r_shadow_offset.x, 1-input.r_shadow_offset.y));
    float4 l_shadow_tex = Decal.Sample(DecalSampler,  float2(input.l_shadow_offset.x, 1-input.l_shadow_offset.y));
    float4 b_shadow_tex = Decal.Sample(DecalSampler,  float2(input.b_shadow_offset.x, 1-input.b_shadow_offset.y));
    
    
    //=============
    //AMBIENT LIGHT
    //=============
    float ambient_ref = 6.5;
    float col_mult = 0.09f;
    float3 ambient_col = float3(col_mult,col_mult,col_mult);
    float3 fog_color = float3(0.1,0.1,0.1);
    float3 fog_color_h = float3(0.01,0.01,0.01);

    ambient_col *= (texture_col.rgb);
    
    float depth = input.depth/10.0f;
    float depth_col = 1-(depth);

    float curve = pow(abs(depth_col),1.5);
    
    float shadow_alpha_threshold = 0.0f;
    float edge_alpha_threshold = 0.5f;
    float3 BLACK = float3(0.0,0.0,0.0);

    
    
    if((input.edge_mask & (uint)(1<<1))) { 
        if(t_edge_tex.a >edge_alpha_threshold) {
            ambient_col = lerp(ambient_col,t_edge_tex.rgb,t_edge_tex.a);
        }
    }
    if((input.edge_mask & (uint)(1<<2))) {
        if(r_edge_tex.a >edge_alpha_threshold) {
            ambient_col = lerp(ambient_col,r_edge_tex.rgb,r_edge_tex.a);
        }
    }
    if((input.edge_mask & (uint)(1<<3))) {
        if(b_edge_tex.a >edge_alpha_threshold) {
            ambient_col = lerp(ambient_col,b_edge_tex.rgb,b_edge_tex.a);
        }
    }
    if((input.edge_mask & (uint)(1<<4))) {
        if(l_edge_tex.a >edge_alpha_threshold) {
            ambient_col = lerp(ambient_col,l_edge_tex.rgb,l_edge_tex.a);
        }
    }
   
    if((input.edge_mask & (uint)(1<<5))) { 
        if(t_shadow_tex.a > shadow_alpha_threshold) {
            ambient_col = lerp(ambient_col,BLACK,t_shadow_tex.a);
        }
    }
    if((input.edge_mask & (uint)(1<<6))) {
        if(r_shadow_tex.a > shadow_alpha_threshold) {
            
            ambient_col = lerp(ambient_col,BLACK,r_shadow_tex.a);
        }
    }
    if((input.edge_mask & (uint)(1<<7))) {
        if(b_shadow_tex.a > shadow_alpha_threshold) {
            ambient_col = lerp(ambient_col,BLACK,b_shadow_tex.a);
        }
    }
    if((input.edge_mask & (uint)(1<<8))) {
        if(l_shadow_tex.a > shadow_alpha_threshold) {
            ambient_col = lerp(ambient_col,BLACK,l_shadow_tex.a);
        }
    }

    if((input.edge_mask & (uint)(1<<9))) {
         ambient_col = lerp(ambient_col,BLACK,0.5f);
        
    }
    
    ambient_col =  lerp(ambient_col,fog_color,curve);
    
    float3 ambient_light = ambient_ref * ambient_col;

    //=============
    //LIGHT PRODUCT
    //=============
    float3 final_lighting = ambient_light;
    //return float4(input.uv.x,input.uv.y,0.0,1.0);
    return float4(final_lighting,1.0);
    
}