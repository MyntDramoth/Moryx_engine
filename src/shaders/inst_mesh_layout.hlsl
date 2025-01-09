
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
    float4 pos_inst :POSITION1;
    float2 uv_inst: TEXCOORD0;

    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 camera_dir: TEXCOORD1;
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    return output;   
}