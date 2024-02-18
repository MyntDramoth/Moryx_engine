
struct PS_INPUT {
    float4 pos: SV_POSITION;
    float3 color: COLOR;
};

cbuffer Constant: register(b0) {
    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    unsigned int time;
};

float4 main(PS_INPUT input): SV_TARGET {
    //return float4(input.color,1.0f);
    return float4(lerp(input.color, float3(1,1,1), (sin(time/100.0f)+1.0f)/2.0f),1.0f);
}