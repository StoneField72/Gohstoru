
#include "../Shader/dxlib_shader/VertexShader.h"

#define LOCAL_WORLD_MAT         g_Base.LocalWorldMatrix


struct VSInput
{
    // 座標( VERTEX3DSHADER構造体の pos の値 )
    float3 Position : POSITION0;

    // 補助座標( VERTEX3DSHADER構造体の spos の値 )
    float4 SubPosition : POSITION1;

    // 法線( VERTEX3DSHADER構造体の norm の値 )
    float3 Normal : NORMAL0;

    // 接線( VERTEX3DSHADER構造体の tan の値 )
    float3 Tangent : TANGENT;

    // 従法線( VERTEX3DSHADER構造体の binorm の値 )
    float3 Binormal : BINORMAL0;

    // ディフューズカラー( VERTEX3DSHADER構造体の dif の値 )
    float4 DiffuseColor : COLOR0;

    // スペキュラカラー( VERTEX3DSHADER構造体の spc の値 )
    float4 SpecularColor : COLOR1;

    // テクスチャ座標０( VERTEX3DSHADER構造体の u, v の値 )
    float2 TextureCoord0 : TEXCOORD0;

    // テクスチャ座標１( VERTEX3DSHADER構造体の su, sv の値 )
    float2 TextureCoord1 : TEXCOORD1;
};

struct VSOutput
{
    float4 Position : SV_POSITION; // 座標
    float4 WorldPos : POSITION0;
    float4 ShadowMapPos : POSITION1;
    float4 Color : COLOR0; // 頂点カラー
    float2 TextureCoord0 : TEXCOORD0; // テクスチャ座標0
    float2 TextureCoord1 : TEXCOORD1; // テクスチャ座標1    
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
   
	// ローカル座標のセット
    float4 localPosition;
    localPosition.xyz = input.Position;
    localPosition.w = 1.0f;

	// 座標計算( ローカル→ビュー→プロジェクション )
    float4 worldPosition;
    worldPosition.x = dot(localPosition, LOCAL_WORLD_MAT[0]);
    worldPosition.y = dot(localPosition, LOCAL_WORLD_MAT[1]);
    worldPosition.z = dot(localPosition, LOCAL_WORLD_MAT[2]);
    worldPosition.w = 1.0f;

	// ワールド座標を保存
	output.WorldPos = worldPosition;

    float4 viewPosition;
    viewPosition.x = dot(worldPosition, g_Base.ViewMatrix[0]);
    viewPosition.y = dot(worldPosition, g_Base.ViewMatrix[1]);
    viewPosition.z = dot(worldPosition, g_Base.ViewMatrix[2]);
    viewPosition.w = 1.0f;

    output.Position.x = dot(viewPosition, g_Base.ProjectionMatrix[0]);
    output.Position.y = dot(viewPosition, g_Base.ProjectionMatrix[1]);
    output.Position.z = dot(viewPosition, g_Base.ProjectionMatrix[2]);
    output.Position.w = dot(viewPosition, g_Base.ProjectionMatrix[3]);
		
	// 法線を計算
    float3 worldNormal;
    worldNormal.x = dot(input.Normal, LOCAL_WORLD_MAT[0].xyz);
    worldNormal.y = dot(input.Normal, LOCAL_WORLD_MAT[1].xyz);
    worldNormal.z = dot(input.Normal, LOCAL_WORLD_MAT[2].xyz);

    float3 viewNormal;
    viewNormal.x = dot(worldNormal, g_Base.ViewMatrix[0].xyz);
    viewNormal.y = dot(worldNormal, g_Base.ViewMatrix[1].xyz);
    viewNormal.z = dot(worldNormal, g_Base.ViewMatrix[2].xyz);   
   
	// ディフューズカラーをセット
    output.Color = input.DiffuseColor;


	// テクスチャ座標のセット
    output.TextureCoord0.x = dot(input.TextureCoord0, g_OtherMatrix.TextureMatrix[0][0]);
    output.TextureCoord0.y = dot(input.TextureCoord0, g_OtherMatrix.TextureMatrix[0][1]);

    output.TextureCoord1.x = dot(input.TextureCoord1, g_OtherMatrix.TextureMatrix[0][0]);
    output.TextureCoord1.y = dot(input.TextureCoord1, g_OtherMatrix.TextureMatrix[0][1]);

	// ワールド座標をシャドウマップ０のライト設定の射影座標に変換
    output.ShadowMapPos.x = dot(worldPosition, g_OtherMatrix.ShadowMapLightViewProjectionMatrix[0][0]);
    output.ShadowMapPos.y = dot(worldPosition, g_OtherMatrix.ShadowMapLightViewProjectionMatrix[0][1]);
    output.ShadowMapPos.z = dot(worldPosition, g_OtherMatrix.ShadowMapLightViewProjectionMatrix[0][2]);

    return output;
}
