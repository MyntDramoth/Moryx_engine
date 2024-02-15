struct VS_INPUT {
    float4 pos: POSITION;
    float3 color: COLOR;
};

struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float3 color: COLOR;
};

cbuffer Constant: register(b0) {
    unsigned int time;
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.pos = lerp(input.pos, input.pos + float4(1,1,1,0), (sin(time/100.0f)+1.0f)/2.0f);
    output.color = input.color;
    return output;   
}