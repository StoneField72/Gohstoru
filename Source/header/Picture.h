#pragma once

#include <DxLib.h>
#include "Object.h"

#define SCREEN_SIZE_X 1280
#define SCREEN_SIZE_Y 720

/*
* é ê^ÉNÉâÉX
*/
class Photo
{
public:
    Photo();
    ~Photo();

    void Initialize();
    void Update();
    void Uninitialize();

    void SetShotScreen();

    int GetSelectPhoto() const { return SelectPhoto; }

    void SavePicture();

    void Decreasefade();

    void DisplayPhoto();

    void DisplayAlbum();

    void SlideAlbum();

    bool GetSlided() const { return Slided; }
    void OffSlided()
    {
        Slided = false;
        slidecount = 0;
    }

private:
    int screenshotScreen;
    int fadeAlpha;
    bool isFadingIn;
    int NotakePicture;
    const int screenshotCount = 10;
    int screenshotGraphs[10];
    int screenshotIndex;

    int Basepoint;
    int BackGraphHandle;
    int ArrowHandle;
    int SelectPhoto;
    int MouseX, MouseY;
    int KeyHitCT;
    bool AlbumShowFlag;

    int slidecount;
    bool Slided;

    bool Good[10];
    int LoveGraphHandle;
    int NotLoveGraphHandle;
    char sourcePath[64]; 
    char destinationPath[64];
    SYSTEMTIME st;
};