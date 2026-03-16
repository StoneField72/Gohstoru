#pragma once
#include "Scene.h"

#define SHADOW_SCALE_X 4096
#define SHADOW_SCALE_Y 4096

#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
#define DOWN_SCALE_SCREEN_W	( 256 )	// ガウスフィルタを掛ける画像の横幅
#define DOWN_SCALE_SCREEN_H	( 256 )	// ガウスフィルタを掛ける画像の縦幅



class GameScene : public Scene 
{
public:
    GameScene();
    virtual ~GameScene();

    void Initialize(void) override;
    void Uninitialize(void) override;
    Scene* Update(void) override;
    void LateUpdate(void) override;
    void Render(void) override;

    void Finish();

private:
    int FinishCount = 0;
    int ItemCount;
    int ItemEffect;

    int UIHandle1;
    int UIHandle2;
    int FinishHandle;
    int ResultHandle;
    int OpenHandle;

    bool Shoot;

    float taskUImoveX;

    int startTime;  // ゲーム開始時に記録
    int timeLimit;  // 制限時間（ミリ秒）＝90秒
    int nowTime;
    int remainingTime; // 秒単位に変換
    SYSTEMTIME st;

    VERTEX2DSHADER SetVertex2D(float x, float y, float u, float v); //頂点データ設定
    void DrawSprite(float x, float y, float width, float height);

    int m_shadowMap;
    int g_Offscreen;       //オフスクリーンバッファ用ハンドル
    int g_Offscreen2;      //オフスクリーンバッファ用ハンドル
    int g_PixelShader = -1;     //ピクセルシェーダー用ハンドル
    int g_PostPixelShader = -1; //ポストエフェクト用ピクセルシェーダー用ハンドル

    VERTEX2DSHADER g_Vertex[4]; //頂点配列
    unsigned short g_Index[6];  //インデックス
    int constBuff;

    COLOR_F g_senddata;

    //ブルーム用
    int highBrightScreen;	// 普通の描画結果から高輝度部分を抜き出した結果を書き込むスクリーン
    int downScaleScreen;	// 高輝度部分を縮小した結果を書き込むスクリーン
    int gaussScreen;	// 縮小画像をガウスフィルタでぼかした結果を書き込むスクリーン

    int gaussRatio;	// ガウスフィルタのぼかし度合い
};
