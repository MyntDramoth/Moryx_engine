struct VS_INPUT {
    float4 pos: POSITION0;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 tangent: TANGENT0;
    float3 binormal: BINORMAL0;
};

struct INST_INPUT {
    float4 inst_pos: POSITION1; // Offset in the texture atlas
    float2 inst_uv: TEXCOORD1; // Scale (size) in the texture atlas
};

struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD1;
    
};

VS_OUTPUT main(INST_INPUT inst_input, INST_INPUT instance) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    return output;   
}