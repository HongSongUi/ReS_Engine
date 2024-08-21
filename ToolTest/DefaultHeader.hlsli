#define g_NumLight 1

Texture2D g_Tex : register(t0);
Texture2D g_MaskTex : register(t1);
Texture2D g_Tex2 :  register(t2);
Texture2D g_Tex3 : register(t3);
Texture2D g_Tex4 : register(t4);
Texture2D g_Tex5 : register(t5);

SamplerState g_SampleWrap : register(s0);

cbuffer cb_data : register(b0)
{
	matrix g_worldMat : packoffset(c0);
	matrix g_viewMat : packoffset(c4);
	matrix g_projMat : packoffset(c8);

	float3 g_LightDir : packoffset(c16);
	float  g_radius1 : packoffset(c16.w);

	float3 g_LightPos : packoffset(c17);
	float  g_radius2 : packoffset(c17.w);

	float3 g_eyeDir : packoffset(c18);
	float g_radius3 : packoffset(c18.w);

	float3 g_eyePos : packoffset(c19);
	float g_radius4 : packoffset(c19.w);

	float g_value1 : packoffset(c20.x);
	float g_value2 : packoffset(c20.y);
	float g_value3 : packoffset(c20.z);
	float g_timer : packoffset(c20.w);
};



float4 ComputePointDiffuseLight(float3 vertexPos, float3 vertexNor, int numLight)
{
	float4 PointLightColor = float4(0, 0, 0, 1);
	float4 LightColor = float4(1, 1, 1, 1);

	float4 Light;
	
	Light.xyz = normalize(vertexPos - g_LightPos.xyz);
	Light.w = distance(vertexPos, g_LightPos.xyz);
	float Luminace = smoothstep(Light.w - 5.0, Light.w, g_radius1);
	float Intensity = saturate(dot(vertexNorm _Light.xyz));
	PointLightColor += float4(LightColor.rgb * Luminac * Intensity, 1.0f);

	return PointLightColor;
}
