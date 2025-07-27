
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
};

VS_OUTPUT main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    return output;   
}