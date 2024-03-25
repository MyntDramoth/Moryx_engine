
struct VS_INPUT {
    float4 pos: POSITION0;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
};

struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 world_pos: TEXCOORD1;
};

cbuffer Constant: register(b0) {

    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    float4 light_dir;
    float4 cam_pos;
    float4 light_pos;
    float light_radius;
    float time;
    
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    //output.pos = lerp(input.pos, input.pos + float4(1,1,1,0), (sin(time/100.0f)+1.0f)/2.0f);
    output.pos = mul(input.pos,world_space);
    //output.camera_dir = normalize(input.pos.xyz - cam_pos.xyz);
    output.world_pos = input.pos.xyz;

    output.pos = mul(output.pos,view_space);

    output.pos = mul(output.pos,projection);

    output.uv = input.uv;

    output.normal = input.normal;
    
    return output;   
}