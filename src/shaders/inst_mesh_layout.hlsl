struct INST_INPUT {
    float4 pos: POSITION1; // Offset in the texture atlas
    float2 uv: TEXCOORD1; // Scale (size) in the texture atlas
};

struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD0;
};


VS_OUTPUT main(INST_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    return output;   
}