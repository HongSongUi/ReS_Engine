struct VS_IN
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXTURE;
};
struct VS_OUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
	float3 w : TEXCOORD1;
	float4 t2 : TEXCOORD3;
};
// 상수버퍼는 레지스터 단위로만 저장된다.
// 레지스터 단위란 :  float4(x,y,z,w)
cbuffer cb_data : register(b0)
{
	matrix g_matWorld : packoffset(c0);
	matrix g_matView : packoffset(c4);
	matrix g_matProj : packoffset(c8);
	matrix g_matWorldInverse : packoffset(c12);

	float3 g_LightDir : packoffset(c16);
	float  g_radius1 : packoffset(c16.w);

	float3 g_LightPos : packoffset(c17);
	float  g_radius2 : packoffset(c17.w);

	float3 g_eyeDir : packoffset(c18);
	float g_radius3 : packoffset(c18.w);

	float3 g_eyePos : packoffset(c19);
	float g_radius4 : packoffset(c19.w);

	float mapWidth : packoffset(c20.x);
	float mapHeight : packoffset(c20.y);
	float g_value3 : packoffset(c20.z);
	float g_timer : packoffset(c20.w);
};

VS_OUT VS(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;
	float4 vLocal = float4(input.p, 1.0f);
	// 중요:  mul 함수는 내적으로 처리된다.
	// vWolrd.x = vLocal dot c0; // 행*행
	// vWolrd.y = vLocal dot c1;
	// vWolrd.z = vLocal dot c2;
	// vWolrd.w = vLocal dot c3;	
	// matrix matTranspose = transpose(g_matWorld);
	float4 vWorld = mul(vLocal, g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	matrix matNormal = transpose(g_matWorldInverse);
	output.p = vProj;
	output.n = normalize(mul(input.n.xyz , matNormal));
	output.c = input.c;
	output.t = input.t;
	output.w = vWorld.xyz;


	float halfW = mapWidth / 2.0f;
	float halfH = mapHeight / 2.0f;
	float W = mapWidth + 1.0f;

	output.t2.x = (vWorld.x + halfW * 1.0f) / W;
	output.t2.y = 1.0f - ((vWorld.z / halfH * 1.0) * 0.5f + 0.5f);
	output.t2.x = output.t2.x * 10.0f;
	output.t2.y = output.t2.y * 10.0f;

	return output;
}

Texture2D		g_txTex				: register(t0);
Texture2D		g_txMaskTex			: register(t1);
Texture2D		g_txTex1			: register(t2);
Texture2D		g_txTex2			: register(t3);
Texture2D		g_txTex3			: register(t4);
Texture2D		g_txTex4			: register(t5);

SamplerState	g_SampleWrap		: register(s0);

float4 LoadTex1Color(float2 uv, float3 world)
{
	float4 color = 0;
	if (world.y <= 8.0f)
	{
		float4 colorA = g_txTex.Sample(g_SampleWrap, uv);
		float4 colorB = g_txTex1.Sample(g_SampleWrap, uv);
		float t = smoothstep(2.0f, 4.0f, world.y);
		color = lerp(colorA, colorB, t);
	}
	return color;
}

float4 LoadTex2Color(float2 uv, float3 world)
{
	float4 color = 0;
	if (world.y > 8.0f && world.y <= 13.0f)
	{
		float4 colorA = g_txTex1.Sample(g_SampleWrap, uv);
		float4 colorB = g_txTex2.Sample(g_SampleWrap, uv);
		float t = smoothstep(8.0f, 10.0f, world.y);
		color = lerp(colorA, colorB, t);
	}
	return color;
}
float4 LoadTex3Color(float2 uv, float3 world)
{
	float4 color = 0;
	if (world.y > 13.0f && world.y <= 18.0f)
	{
		float4 colorA = g_txTex2.Sample(g_SampleWrap, uv);
		float4 colorB = g_txTex3.Sample(g_SampleWrap, uv);
		float t = smoothstep(13.0f, 15.0f, world.y);
		color = lerp(colorA, colorB, t);
	}
	return color;

}float4 LoadTex4Color(float2 uv, float3 world)
{
	float4 color = 0;
	if (world.y > 18.0f && world.y <= 25.0f)
	{
		float4 colorA = g_txTex3.Sample(g_SampleWrap, uv);
		float4 colorB = g_txTex4.Sample(g_SampleWrap, uv);
		float t = smoothstep(18.0f, 20.0f, world.y);
		color = lerp(colorA, colorB, t);
	}
	return color;
}
float4 LoadTex5Color(float2 uv, float3 world)
{
	float4 color = 0;
	if (world.y > 25.0f)
	{
		color = g_txTex4.Sample(g_SampleWrap, uv);
	}
	return color;

}

float4 PS(VS_OUT input) : SV_Target
{

	float4 vColor = g_txTex.Sample(g_SampleWrap , input.t2.xy);

	//float4 vColor = LoadTex1Color(input.t2.xy, input.w);
	//vColor += LoadTex2Color(input.t2.xy, input.w);
	//vColor += LoadTex3Color(input.t2.xy, input.w);
	//vColor += LoadTex4Color(input.t2.xy, input.w);
	//vColor += LoadTex5Color(input.t2.xy, input.w);


	float4 mask = g_txMaskTex.Sample(g_SampleWrap, input.t.xy);
	
	float4 ColorTile = g_txTex1.SampleLevel(g_SampleWrap, input.t.xy * 10.0f, 0) * mask.r;
	ColorTile += g_txTex2.SampleLevel(g_SampleWrap, input.t.xy * 10.0f, 0) * mask.g;
	ColorTile += g_txTex3.SampleLevel(g_SampleWrap, input.t.xy * 10.0f, 0) * mask.b;
	ColorTile += g_txTex4.SampleLevel(g_SampleWrap, input.t.xy * 10.0f, 0) * mask.a;
	
	float4 BlendColor = 0;
	BlendColor.r = max(vColor.r, ColorTile.r);
	BlendColor.g = max(vColor.g, ColorTile.g);
	BlendColor.b = max(vColor.b, ColorTile.b);
	BlendColor.a = max(vColor.a, ColorTile.a);

	float4 LightColor = float4(1, 1, 1, 1);

	float3 WorldLightDir = normalize(-g_LightDir.xyz);
	
	float Intencity = saturate(dot(WorldLightDir, input.n));
	float4 Diffuse = float4(LightColor.rgb * Intencity,1.0f);

	float3 light = reflect(-g_LightDir, input.n);

	float specIntencity = pow(saturate(dot(-g_eyeDir, light.xyz)), 30.0f);


	float4 Spec = float4(LightColor.rgb * specIntencity, 1.0f);
	
	float4 vAmbintColor = float4(0.3f, 0.3f, 0.3f, 1.0f);

	float4 FinalColor = BlendColor * (vAmbintColor+Diffuse);

	return FinalColor;
}