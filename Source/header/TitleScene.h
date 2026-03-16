#pragma once

#include "Scene.h"

class TitleScene : public Scene
{
public:
    TitleScene();
    virtual ~TitleScene();

    void Initialize(void) override;
    void Uninitialize(void) override;
    Scene* Update(void) override;
    void LateUpdate(void) override;
    void Render(void) override;

private:
    int GraphHandle2;

    int MenuHandle;
    int SelectHandle;
    int selectAlpha;
    bool alphaUp;
    int backHandle;
    int BGMtextHandle;
    int SEtextHandle;
    int GoodPhotoGraphHandle;
    int MeetGhostGraphHandle;

    int FontHandle;
    int FontHandle2;

    int SkyHandle;
    int GhostHandle;
    int GroundHandle;
    int TreeHandle[5];
    int CameraHandle;
    int TitleTextHandle;
    int InCameraGraphHandle;
    int backgroundScreen;
    int CameraFrameHandle;
    int GameStartGraphHandle;
    int SettingGraphHandle;
    int PhotoGraphHandle;
    int StartIconGraphHandle;
    int VolumeUpGraphHandle;
    int VolumeDownGraphHandle;
    int MenutextGraphHandle;
    int RightGraphHandle;
    int LeftGraphHandle;

    int texHandle;
    int treetexHandle;

    VERTEX3D Vertex[4];
    WORD Index[6];

    int TitleType;
    int BottunCoolTime;
    int Mode;
    int Menu;
    int Choice;
    int CameraX;
    int MouseX;
    int MouseY;
    float windOffset;

    int DispGhostType;

    bool KeyInputflag;

    int BGMVolume;
    int SEVolume;

    int EnemyHandle[6];
    int EnemyTexHandle[9];
    float ModelY;
    int GhostNameHandle[6];

    int SavePhoto[10];
    int SaveSelect;
    char savefilename[64];
};