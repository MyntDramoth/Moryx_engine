struct INST_INPUT {
    float4 pos: INSTANCE_POS0;
    float2 uv: INSTANCE_UV0;
};


struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float2 uv: INSTANCE_UV0;
};

VS_OUTPUT main(INST_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    return output;   
}