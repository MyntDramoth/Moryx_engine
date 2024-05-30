
struct VS_INPUT {
    float4 pos: POSITION0;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    float3 tangent: TANGENT0;
    float3 binormal: BINORMAL0;
};

struct VS_OUTPUT {
    float4 pos :SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
};

cbuffer Constant: register(b0) {

    row_major float4x4 world_space;
    row_major float4x4 view_space;
    row_major float4x4 projection;
    
};

VS_OUTPUT vs_main(VS_INPUT input) {
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.pos = mul(input.pos, world_space);
	output.pos = mul(output.pos, view_space);
	output.pos = mul(output.pos, projection);
	output.uv = input.uv;
	output.normal = normalize(mul(input.normal, (float3x3)world_space));
    return output;   
}

Texture2D Color: register(t0);
sampler ColorSampler: register(s0);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 normal: NORMAL0;
    
};

float4 ps_main(PS_INPUT input): SV_TARGET {
    
    
   float4 color = Color.Sample(ColorSampler, input.uv);
	float3 light_direction = normalize(float3(-1, 1, 1));


	//AMBIENT LIGHT
	float ka = 8.5;
	float3 ia = float3(0.09, 0.082, 0.082);
	ia *= (color.rgb);

	float3 ambient_light = ka * ia;

	//DIFFUSE LIGHT
	float kd = 0.7;
	float amount_diffuse_light = max(dot(light_direction.xyz, input.normal),0.0);
	float3 id = float3(1, 1, 1);
	id *= (color.rgb);
	float3 diffuse_light = kd * id * amount_diffuse_light;

	//SPECULAR LIGHT
	//float ks = 0.0;
	//float3 is = float3(1.0, 1.0, 1.0);
	//float3 reflected_light = reflect(m_light_direction.xyz, input.normal);
	//float shininess = 30.0;
	//float amount_specular_light = pow(max(0.0, dot(reflected_light, input.direction_to_camera)), shininess);

	//float3 specular_light = ks * amount_specular_light * is;

	float3 final_light = ambient_light + diffuse_light /*+ specular_light*/;

	return float4(final_light,1.0);
}