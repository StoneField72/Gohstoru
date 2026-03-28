#include "../Shader/dxlib_shader/PixelShader.h"

// 頂点シェーダー・ピクセルシェーダー共通パラメータ
cbuffer cbRECIEVE : register(b4)
{
    float4 g_RecieveData;
};


SamplerState g_SrcSampler       : register( s0 ) ;
Texture2D    g_SrcTexture       : register( t0 ) ;

SamplerState g_BlendSampler     : register( s1 ) ;
Texture2D    g_BlendTexture	    : register( t1 ) ;


struct PS_INPUT
{
    float4 Position : SV_POSITION; // 座標
    float4 DiffuseColor : COLOR0; // ディフューズカラー
    float2 TextureCoord0 : TEXCOORD0; // テクスチャ座標０
    float2 TextureCoord1 : TEXCOORD1; // テクスチャ座標１
};

float rand(float2 co)
{
    return frac(sin(dot(co, float2(12.9898, 78.233))) * 43758.5453);
}

float4 ps_post(PS_INPUT In) : SV_TARGET0
{
    float4 DestColor;
    
    float4 color = g_SrcTexture.Sample(g_SrcSampler, In.TextureCoord0);
    color += abs(sin(In.TextureCoord0.y * 100.0 + g_RecieveData.x * 5.0)) * 0.045;
    color += abs(sin(In.TextureCoord0.y * 300.0 - g_RecieveData.x * 10.0)) * 0.03;
    color.a = 1.0;
    //color.rgb = pow(color.rgb, 0.9); // ガンマ補正で明るく
    
    // --- フィルムグレイン --- 
    float noise = rand(In.TextureCoord0 * g_RecieveData.x * 120.0); 
    float grainStrength = 0.1; 
    // ノイズの強さ（0.02?0.06 推奨） 
    color.rgb += (noise - 0.5) * grainStrength;
    
    DestColor = color;
    
    return DestColor;
}
