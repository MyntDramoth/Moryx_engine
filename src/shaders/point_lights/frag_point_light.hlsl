//the names of the Texture and sampler variables HAVE TO BE THESE NAMES TO WORK!!!!!!!!!!!!!!!!!!!
Texture2D Texture: register(t0);
sampler TextureSampler : register(s0);

Texture2D Normal: register(t1);
sampler NormalSampler : register(s1);

struct PS_INPUT {
    float4 pos: SV_POSITION;
    float2 uv: TEXCOORD0;
    float3 world_pos: TEXCOORD1;
    row_major float3x3 tbn: TEXCOORD2;
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

float4 main(PS_INPUT input): SV_TARGET {
    
    float4 texture_col = Texture.Sample(TextureSampler,float2(input.uv.x,1.0 - input.uv.y));
    float4 normal = Normal.Sample( NormalSampler,float2(input.uv.x,1.0 - input.uv.y));

    float3 camera_dir = normalize(input.world_pos.xyz - cam_pos.xyz);

    normal.xyz = (normal.xyz * 2.0f) - 1.0f;
    normal.xyz = mul(normal.xyz,input.tbn);

    

    //=============
    //AMBIENT LIGHT
    //=============
    float ambient_ref = 1.5;
    float3 ambient_col = float3(0.09,0.082,0.082);
    ambient_col *= (texture_col.rgb * 0.03f);
    float3 ambient_light = ambient_ref * ambient_col;

    //=============
    //DIFFUSE LIGHT
    //=============


    float diffuse_ref = 0.7;
    float3 light_dir_point = normalize(light_pos.xyz - input.world_pos.xyz);
    float light_dist_point = length(light_pos.xyz - input.world_pos.xyz);
    float light_fade_area = max(0.0f,light_dist_point - light_radius);

    float const_func =  1.0f;
    float linear_func =  1.0f;
    float quadratic_func =  1.0f;

    float attenuation =const_func + linear_func * light_fade_area + quadratic_func * light_fade_area * light_fade_area;


    float3 diffuse_col_day = texture_col.rgb;
   

    float diffuse_light_amount = max(0.0,dot(light_dir_point.xyz,normal.xyz));

   

    float3 diffuse_light = (diffuse_ref * diffuse_col_day * diffuse_light_amount) / attenuation;

    float dot_nl = dot(light_dir_point.xyz, input.tbn[2]);

    //==============
    //SPECULAR LIGHT
    //==============
    float spec_ref = 1.0f;
    float3 spec_col = float3(1.0,1.0,1.0);
    float3 ref_light = reflect(light_dir_point.xyz,normal.xyz);
    float shine_factor = 30.0f;
    float spec_light_amount = 0.0f;

    if(dot_nl > 0) {
        spec_light_amount = pow(max(0.0,dot(ref_light,camera_dir)),shine_factor);
    }

    float3 specular_light = (spec_ref * spec_light_amount * spec_col) / attenuation;

    //=============
    //LIGHT PRODUCT
    //=============
    float3 final_lighting = specular_light + diffuse_light + ambient_light;

    

    return float4(final_lighting,1.0);
    //return Texture.Sample(TextureSampler,input.uv * 0.5);
}