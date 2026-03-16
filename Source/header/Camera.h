#pragma once
#include <DxLib.h>

#define SCREEN_SIZE_X 1280
#define SCREEN_SIZE_Y 720

class Player;

/*
* カメラクラス
*/
class Camera
{
public:
    Camera();
    ~Camera();

    void Initialize(Player* player);
    void Update();

    float GetHorizontalAngle() { return mfHorizontalAngle; }
    float GetVerticalAngle() { return mfVerticalAngle; }

    VECTOR GetPosition() { return mvPosition; }
    VECTOR GetLookAtPosition() { return mvLookAtPosition; }

    void SetTime(int t) { GameTime = t; }

    void SetZoom(int z) { zoom = z; }

private:
    int diffX;
    int diffY;

    float mfHorizontalAngle;    // 水平方向アングル
    float mfVerticalAngle;      // 垂直方向アングル

    VECTOR tempPosition2;

    VECTOR mvPosition;          // カメラ位置
    VECTOR mvLookAtPosition;    //カメラ注視点

    Player* mpPlayer;           //プレイヤーポインタ

    bool skyCamera;

    const float ANGLE_SPEED = 3.0f;

    int mouseX;
    int mouseY;

    int zoom;

    float StartCamera;
    int GameTime;

    float windOffset;

    bool Menu;
    int CT;
    int CurMouseX;
    int CurMouseY;
};
