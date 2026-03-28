#pragma once


#include <DxLib.h>
#include "Object.h"

#define Ball_Count 55
#define WIDTH  38	// 数字グラフィック横幅
#define HEIGHT 42	// 数字グラフィック高さ


/*
* カメラクラス
*/
class Shot
{
public:
    Shot();
    ~Shot();

    void Initialize();
    void Update();

    void UIRender();

    void CameraRange(GameObject* parent);

    void Shutter();

    void FinderScreen();
    void Finder();

    void SpherePos_Init();

    //当たり判定
    void CameraCheck(GameObject* parent);

    void Cooltime();

    int GetCoolTime() { return Shuttercooltime; }

    bool GetTurn() { return Turn; }
    int GetTWait() { return TurnWait; }

    int GetScore(void) { return score; }

    int GetFilmcount() { return filmCount; }

    int FilmScore(int f) const { return film[f]; }

    int GetTotalScore() const { return TotalScore; }

    void SetGameTime(int i) { GameTime = i; }
    int GetGameTime() const { return GameTime; }

    // 数値をグラフィック表示する関数
    void NumDraw(int Num, int x, int y);

private:
    VECTOR BallPos[Ball_Count];
    VECTOR CameraCollisionCenter[10];//列
    int  SideBallCount[10];//列
    bool hitFlag[Ball_Count];
    
    VECTOR camDir;
    float angleY;
    VECTOR front;
    VECTOR up;
    VECTOR right;

    VECTOR shotCore;//当たり判定の中心
    float distance;//距離

    int score;//その写真のスコア
    int film[10];//その写真のスコア（保存用）
    int filmCount;//写真の残り枚数
    bool ShutterCoolDown;//シャッターのクールタイムに入っているかのフラグ
    int  Shuttercooltime;//シャッターのクールタイム

    int enemyCount;//何体敵が写っているかのカウント
    int Bonus;//ボーナスとして追加するスコア

    int GraphHandle1;
    int GraphHandle2;
    int GraphHandle3;
    int UIHandle1;
    int UIHandle2;
    int UIHandle3;
    int UIHandle4;
    int UIHandle5;

    int FontHandle1;

    int NumburGraphHandle[10];

    int TotalScore;//合計スコア
    int GameTime;//ゲーム内時間

    bool Turn;
    int TurnWait;
};
