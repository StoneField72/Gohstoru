#pragma once

class Fade
{
public:
    Fade();
    virtual ~Fade();

    void FadeOut();//フェードアウト
    void FadeIn();//フェードイン

    void WaitFade();//フェード待機

    bool GetFadeIn(){ return FadebleIn; }
    void SetFadeIn(bool b) {
        if (!FadebleOut)
        {
            
        }

        FadebleOut = false;
        ChangeScene = false;
        FadebleIn = b;
    }

    bool GetFadeOut() { return FadebleOut; }
    void SetFadeOut(bool b) {
        if (!FadebleIn)
        {
            FadebleOut = b;
        }
    }

    bool GetChangeScene() { return ChangeScene; }
    void SetChangeScene(bool b) { ChangeScene = b; }

private:
    bool FadebleIn;//フェードインフラグ
    bool FadebleOut;// フェードアウトフラグ
    bool ChangeScene;//シーン遷移フラグ

    int alpha = 0;//フェード用
};
