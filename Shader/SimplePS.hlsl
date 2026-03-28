#include "../Shader/dxlib_shader/PixelShader.h"

// シャドウマップパラメータ
cbuffer cbCamera : register(b4)
{
    float4	CameraPos;
    float4	LightDir;
};

SamplerState g_SrcSampler       : register(s0);
Texture2D    g_SrcTexture       : register(t0);

Texture2D    g_NormalTexture	: register(t1);

SamplerState g_ShadowMap0Sampler : register(s8); // シャドウマップ０テクスチャ
Texture2D    g_ShadowMap0Texture : register(t8); // シャドウマップ０テクスチャ


struct PS_INPUT
{
    float4 Position      : SV_POSITION; // 座標
    float4 WorldPos      : POSITION0;
    float4 ShadowMapPos  : POSITION1;
    float4 Color         : COLOR0; // 頂点カラー
    float2 TextureCoord0 : TEXCOORD0; // テクスチャ座標0
    float2 TextureCoord1 : TEXCOORD1; // テクスチャ座標1
};

//
float4 ps_simple(PS_INPUT input) : SV_TARGET0
{
	float4 TexColor ;
	float4 DestColor ;

    TexColor = g_SrcTexture.Sample(g_SrcSampler, input.TextureCoord0);

    /////////////////////////////////////////////////////////
	// 法線マップによる凹凸表現
    /////////////////////////////////////////////////////////
	float4 NormalTex;
	NormalTex = g_NormalTexture.Sample(g_SrcSampler, input.TextureCoord0);
	NormalTex = NormalTex * 2.0f - 1.0f;// 法線マップの値を -1.0f ～ 1.0f の範囲に変換

	// 法線ベクトルの算出
    float4 normal;
	normal.x = NormalTex.r;
	normal.y = NormalTex.b;
	normal.z = NormalTex.g;
    normal.w = 0.0f;
    normal = normalize(normal);

	float light = -dot(LightDir, normal);
    light = saturate(light);

    /////////////////////////////////////////////////////////
	// ブリンフォンによるスペキュラ計算
    /////////////////////////////////////////////////////////
    float3 eye = input.WorldPos.xyz - CameraPos.xyz;
	eye = normalize(eye);
	float3 halfVec = normalize(LightDir.xyz + eye);
	float spec = pow(saturate(-dot(normal.xyz, halfVec)), 10);

    /////////////////////////////////////////////////////////
	// シャドウマップによる影処理
    /////////////////////////////////////////////////////////
    float depth = 1.0;
    float2 DepthTexCoord;
    float4 TextureDepth;
   
		// 頂点のテクスチャ座標値が範囲内の場合のみ処理する
    if (input.ShadowMapPos.x < -1.0f || input.ShadowMapPos.x > 1.0f ||
		input.ShadowMapPos.y < -1.0f || input.ShadowMapPos.y > 1.0f ||
		input.ShadowMapPos.z < 0.0f || input.ShadowMapPos.z > 1.0f)
    {
        depth = 1.0f;
    }
    else
    {
		// 深度テクスチャの座標を算出
		// PSInput.ShadowMap0Pos.xy は -1.0f ～ 1.0f の値なので、これを 0.0f ～ 1.0f の値にする
        DepthTexCoord.x = (input.ShadowMapPos.x + 1.0f) / 2.0f;

		// yは更に上下反転
        DepthTexCoord.y = 1.0f - (input.ShadowMapPos.y + 1.0f) / 2.0f;

		// 深度バッファテクスチャから深度を取得
        TextureDepth = g_ShadowMap0Texture.Sample(g_ShadowMap0Sampler, DepthTexCoord);

		// テクスチャに記録されている深度( +補正値 )よりＺ値が大きかったら奥にあるということで減衰率を最大にする
        //depth = smoothstep(input.ShadowMapPos.z - g_ShadowMap.Data[0].GradationParam, input.ShadowMapPos.z, TextureDepth.r + g_ShadowMap.Data[0].AdjustDepth);

        if (TextureDepth.r + g_ShadowMap.Data[0].AdjustDepth < input.ShadowMapPos.z - 0.001)
            depth = 0.5;
    }

    /////////////////////////////////////////////////////////
	// 出力色の計算
    /////////////////////////////////////////////////////////
    DestColor.rgb = (TexColor.rgb + spec) * depth * light;
	saturate(DestColor.rgb);
    DestColor.a = 1.0;
	
    return DestColor;
}
