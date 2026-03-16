#pragma once

#include "Scene.h"

class ResultScene : public Scene
{
public:

    ResultScene();
    virtual ~ResultScene();

    void Initialize(void) override;
    void Uninitialize(void) override;
    Scene* Update(void) override;
    void LateUpdate(void) override;
    void Render(void) override;

private:
    int FontHandle;
    int FontHandle2;

    int GoodGraphHandle;
    int BackTitleGraphHandle;
    int GoalbumGraphHandle;
    int ClosealbumGraphHandle;
    int MouseX, MouseY;

    int SGraphHandle;
    int AGraphHandle;
    int BGraphHandle;
    int CGraphHandle;
    int DGraphHandle;
    int TotalScoreHandle;
    int RankGraphHandle;
    int BackGraphHandle;
    int ScoreGraphHandle;

    int KeyHitCT;
    bool ShowPhoto;
};