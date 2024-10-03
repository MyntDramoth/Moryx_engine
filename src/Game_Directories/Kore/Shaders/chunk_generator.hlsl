

struct BufType
{
    int i;
    float f;
    double d;
};

struct PS_INPUT {
    float4 pos: SV_POSITION;
};

StructuredBuffer<BufType> Buffer0 : register(t0);
StructuredBuffer<BufType> Buffer1 : register(t1);
RWStructuredBuffer<BufType> BufferOut : register(u0);


[numthreads(32, 32, 32)]
void main(uint3 id : SV_DispatchThreadID){
    Buffer0[id.x].i = 0;
    Buffer0[id.y].f = 0;
    Buffer0[id.z].i = 0;
};