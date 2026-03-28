#include "DxLib.h"
#include "Fade.h"

Fade::Fade()
{
    FadebleIn = TRUE;
    FadebleOut = FALSE;
    ChangeScene = FALSE;

    alpha = 255;
}

Fade::~Fade()
{
}

//alpha = 　0 完全透過（■が写らない）
//alpha = 255 完全不透過（■が透けない）
// 
//フェードアウト
void Fade::FadeOut()
{
    alpha += 3;//アルファを少しずつ増やす

    if (alpha >= 255)
    {
        alpha = 255;

        ChangeScene = TRUE;//シーン遷移フラグを真にする
        //FadebleOut = FALSE;//フェードアウトが完了したらフラグを偽にする
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);    // 写真の枠を描画
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //DrawCircle(1280 / 2, 720 / 2, (alpha * 5), 0, TRUE);
}

//フェードイン
void Fade::FadeIn()
{
    alpha -= 3;//アルファを少しずつ減らす

    if (alpha <= 0)
    {
        alpha = 0;

        FadebleIn = FALSE;//フェードインフラグを偽にする
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);    // 写真の枠を描画
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //DrawCircle(1280 / 2, 720 / 2, (alpha * 5), 0, TRUE);
}

//フェードフラグが真になるのを待つ
void Fade::WaitFade()
{
    if (FadebleOut == true)
    {
        FadeOut();
    }
    else if (FadebleIn == true)
    {
        FadeIn();
    }
}