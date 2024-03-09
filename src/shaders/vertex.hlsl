struct VS_INPUT {
    float4 pos: POSITION0;
    float2 uv: TEXCOORD0;
};

struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD0;
};

cbuffer Constant: register(b0) {

    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    unsigned int time;
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    //output.pos = lerp(input.pos, input.pos + float4(1,1,1,0), (sin(time/100.0f)+1.0f)/2.0f);
    output.pos = mul(input.pos,world_space);

    output.pos = mul(output.pos,view_space);

    output.pos = mul(output.pos,projection);

    output.uv = input.uv;
    
    return output;   
}