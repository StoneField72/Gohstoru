#include "DxLib.h"

#include "Camera.h"
#include "game_player.h"
#include <math.h>
#include "Collision.h"
#include <list>
#include "Shooting.h"
#include "DxLibUtil.h"

#define D2R(deg) ((deg)*DX_PI_F/ 180.0f)

Camera::Camera()
    : mfHorizontalAngle(0.0f)
    , mfVerticalAngle(0.0f)
    , mpPlayer(nullptr)
    , zoom(0)
    , skyCamera(false)
    , StartCamera(100.0f)
    , GameTime(0)
    , windOffset(0.0f)
    ,Menu(false)
    ,CT(0)
    ,CurMouseX(0)
    ,CurMouseY(0)
{

}

Camera::~Camera()
{

}


void Camera::Initialize(Player* player)
{
    mfHorizontalAngle = 0.0f;
    mfVerticalAngle = 20.0f;

    diffX = SCREEN_SIZE_X;
    diffY = SCREEN_SIZE_Y;

    //プレイヤーの情報を保持しておく
    mpPlayer = player;

    tempPosition2 = VGet(0.0f, 0.0f, 0.0f);

    // カメラの位置と向きを設定
    SetCameraPositionAndTarget_UpVecY(
        VGet(0.0f, 100.0f, -1000.0f),
        VGet(0.0f, 100.0f, 0.0f)
    );

    // カメラのクリッピング距離を設定
    SetCameraNearFar(18.0f, 100000.0f);

    skyCamera = false;

    StartCamera = 100.0f;
    GameTime = 0;

    // 背景の色を灰色にする
    //SetBackgroundColor(128, 128, 128);
    SetBackgroundColor(35, 59, 108);//夜
    //SetBackgroundColor(137, 189, 222);

    // Zバッファに書き込む準備
    SetUseZBufferFlag(true);
    SetWriteZBufferFlag(true);

    SetMouseDispFlag(FALSE);
}


void Camera::Update()
{
    if (GameTime <= 90)
    {
        if (CT > 0)
        {
            CT--;
        }

        if (CheckHitKey(KEY_INPUT_M) && CT == 0)
        {
            if (Menu == false)
            {
                Menu = true;
                SetMouseDispFlag(TRUE);
                //GetMousePoint(&CurMouseX, &CurMouseY);
            }
            else
            {
                Menu = false;
                SetMouseDispFlag(FALSE);
                //SetMousePoint(CurMouseX, CurMouseY);
            }

            CT = 20;
        }

        if (CheckHitKey(KEY_INPUT_N) && CT == 0)
        {
            if (skyCamera == false)
            {
                skyCamera = true;
            }
            else
            {
                skyCamera = false;
            }
            CT = 20;
        }

        
        GetMousePoint(&mouseX, &mouseY);

        diffX = SCREEN_SIZE_X / 2 - mouseX;
        diffY = SCREEN_SIZE_Y / 2 - mouseY;

        mfHorizontalAngle += (float)diffX * 0.05f; //(diffX / 2) / 2
        mfVerticalAngle += (float)(-diffY / 2) * 0.05f;

        Shot *pshot = new Shot();

        if (pshot->GetTurn() == true)
        {
            if (mfVerticalAngle >= 15.0f)
            {
                mfVerticalAngle = 15.0f;
            }
            if (mfVerticalAngle <= -10.0f)
            {
                mfVerticalAngle = -10.0f;
            }
        }


        /*if (CheckHitKey(KEY_INPUT_LEFT) == 1)
        {
            mfHorizontalAngle += 3.0f;
            if (mfHorizontalAngle >= 180.0f)
            {
                mfHorizontalAngle -= 360.0f;
            }
        }
        if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
        {
            mfHorizontalAngle -= 3.0f;
            if (mfHorizontalAngle <= -180.0f)
            {
                mfHorizontalAngle += 360.0f;
            }
        }
        if (CheckHitKey(KEY_INPUT_DOWN) == 1)
        {
            mfVerticalAngle += 3.0f;
            if (mfVerticalAngle >= 80.0f)
            {
                mfVerticalAngle = 80.0f;
            }
        }
        if (CheckHitKey(KEY_INPUT_UP) == 1)
        {
            mfVerticalAngle -= 3.0f;
            if (mfVerticalAngle <= -20.0f)
            {
                mfVerticalAngle = -20.0f;
            }
        }*/


        if (mfHorizontalAngle >= 180.0f)
        {
            mfHorizontalAngle -= 360.0f;
        }
        if (mfHorizontalAngle <= -180.0f)
        {
            mfHorizontalAngle += 360.0f;
        }
        if (mfVerticalAngle >= 80.0f)
        {
            mfVerticalAngle = 80.0f;
        }
        if (mfVerticalAngle <= -20.0f)
        {
            mfVerticalAngle = -20.0f;
        }

        // カメラの位置と向きを設定
        {
            tempPosition2 = VGet(0.0f, 0.0f, 0.0f);

            // 注視点はキャラクターモデルの座標から少し高い位置にしておく
            mvLookAtPosition = mpPlayer->GetPos();
            mvLookAtPosition.y += 150.0f + windOffset;

            // 球面座標(3次元の極座標)への変換式を使う
            tempPosition2.x = 10.0f * cosf(mfVerticalAngle / 180.0f * DX_PI_F) * sinf(mfHorizontalAngle / 180.0f * DX_PI_F);
            tempPosition2.y = 10.0f * sinf(mfVerticalAngle / 180.0f * DX_PI_F);
            tempPosition2.z = -(10.0f * cosf(mfVerticalAngle / 180.0f * DX_PI_F) * cosf(mfHorizontalAngle / 180.0f * DX_PI_F));

            if (Menu == false)
            {
                // 算出した座標に注視点の位置を加算したものがカメラの位置
                mvPosition = VAdd(tempPosition2, mvLookAtPosition);

                if (GetPlayerObject()->GetSpeed() > 0.0f)
                {
                    windOffset = sin(GetNowCount() * 0.008f) * 8; // ゆらゆら動く値
                }
                else
                {
                    windOffset = sin(GetNowCount() * 0.002f) * 8; // ゆらゆら動く値
                } 
            }

            if (skyCamera)
            {
                //カメラを上空に置く
                SetCameraPositionAndTarget_UpVecY(VAdd(mvPosition, VGet(0.0f, 12000.0f, 0.0f)), mvLookAtPosition);
            }
            else
            {
                // カメラの設定に反映する
                SetCameraPositionAndTarget_UpVecY(mvPosition, mvLookAtPosition);
            }
        }
    }
    else
    {
        mfHorizontalAngle += 0.65f;

        if (GameTime > 91)
        {
            StartCamera += 2.5f;
        }
        else
        {
            StartCamera -= 7.0f;
        }

        mvLookAtPosition = mpPlayer->GetPos();
        mvLookAtPosition.y += 150.0f;
        // 球面座標(3次元の極座標)への変換式を使う
        tempPosition2.x = StartCamera * cosf(mfVerticalAngle / 180.0f * DX_PI_F) * sinf(mfHorizontalAngle / 180.0f * DX_PI_F);
        tempPosition2.y = StartCamera * sinf(mfVerticalAngle / 180.0f * DX_PI_F);
        tempPosition2.z = -(StartCamera * cosf(mfVerticalAngle / 180.0f * DX_PI_F) * cosf(mfHorizontalAngle / 180.0f * DX_PI_F));

        // 算出した座標に注視点の位置を加算したものがカメラの位置
        mvPosition = VAdd(tempPosition2, mvLookAtPosition);

        // カメラの設定に反映する
        SetCameraPositionAndTarget_UpVecY(mvPosition, mvLookAtPosition);
    }


    if (Menu == false)
    {
        SetMousePoint(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
    }
}
