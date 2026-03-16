#include "DxLib.h"
#include "SoundManager.h"

Sound::Sound()
{
    BGMVolume = 50;
    SEVolume = 50;

    ClickSEHandle = -1;
    ShutterSEHandle = -1;
    RollSEHandle = -1;
    LookSEHandle = -1;
    SommerSEHandle = -1;
    WindSEHandle = -1;
    WalkSEHandle = -1;
}

Sound::~Sound()
{
}


void Sound::Initialize()
{
    ClickSEHandle = LoadSoundMem("Resource/Sound/Click.mp3");
    ShutterSEHandle = LoadSoundMem("Resource/Sound/Shutter.mp3");
    RollSEHandle = LoadSoundMem("Resource/Sound/ティンパニロール.mp3");
    LookSEHandle = LoadSoundMem("Resource/Sound/警告音1.mp3");
    SommerSEHandle = LoadSoundMem("Resource/Sound/夏の山1.mp3");
    WindSEHandle = LoadSoundMem("Resource/Sound/風に揺れる草木1.mp3");
    WalkSEHandle = LoadSoundMem("Resource/Sound/芝生の上を歩く.mp3");
}

void Sound::Uninitialize()
{
    DeleteSoundMem(ClickSEHandle);
    DeleteSoundMem(ShutterSEHandle);
    DeleteSoundMem(RollSEHandle);
    DeleteSoundMem(LookSEHandle);
    DeleteSoundMem(SommerSEHandle);
    DeleteSoundMem(WindSEHandle);
    DeleteSoundMem(WalkSEHandle);
}

void Sound::Update()
{

}

void Sound::PlayBGM(int BGMnum)
{
    
}

void Sound::PlaySE(int SEnum)
{
    switch (SEnum)
    {
    case 0:
        if (CheckSoundMem(ClickSEHandle) == 0)
        {
            PlaySoundMem(ClickSEHandle, DX_PLAYTYPE_BACK);
        }
        break;

    case 1:
        if (CheckSoundMem(ShutterSEHandle) == 0)
        {
            PlaySoundMem(ShutterSEHandle, DX_PLAYTYPE_BACK);
        }
        break;

    case 2:
        if (CheckSoundMem(RollSEHandle) == 0)
        {
            PlaySoundMem(RollSEHandle, DX_PLAYTYPE_BACK);
        }
        break;

    case 3:
        if (CheckSoundMem(LookSEHandle) == 0)
        {
            PlaySoundMem(LookSEHandle, DX_PLAYTYPE_BACK);
        }  
        break;

    case 4:
        if (CheckSoundMem(SommerSEHandle) == 0)
        {
            PlaySoundMem(SommerSEHandle, DX_PLAYTYPE_BACK);
        }
        break; 

    case 5:
        if (CheckSoundMem(WindSEHandle) == 0)
        {
            PlaySoundMem(WindSEHandle, DX_PLAYTYPE_BACK);
        }
        break;    
    
    case 6:
        if (CheckSoundMem(WalkSEHandle) == 0)
        {
            PlaySoundMem(WalkSEHandle, DX_PLAYTYPE_BACK);
        }
        break;

    }
}

void Sound::StopBGM(int BGMnum)
{

}

void Sound::StopSE(int SEnum)
{
    switch (SEnum)
    {
    case 0:
        StopSoundMem(ClickSEHandle);
        break;

    case 1:
        StopSoundMem(ShutterSEHandle);
        break;

    case 2:
        StopSoundMem(RollSEHandle);
        break;

    case 3:
        StopSoundMem(LookSEHandle);
        break;

    case 4:
        StopSoundMem(SommerSEHandle);
        break;    

    case 5:
        StopSoundMem(WindSEHandle);
        break;   

    case 6:
        StopSoundMem(WalkSEHandle);
        break;

    }
}

void Sound::ChangeBGMVolume(int Volume)
{
    BGMVolume = Volume;
}

void Sound::ChangeSEVolume(int Volume)
{
    SEVolume = Volume;

    ChangeVolumeSoundMem(255 * Volume / 100, ClickSEHandle);
    ChangeVolumeSoundMem(255 * Volume / 100, ShutterSEHandle);
    ChangeVolumeSoundMem(255 * Volume / 100, RollSEHandle);
    ChangeVolumeSoundMem(255 * Volume / 100, LookSEHandle);
    ChangeVolumeSoundMem(255 * Volume / 100, SommerSEHandle);
    ChangeVolumeSoundMem(255 * Volume / 100, WindSEHandle);
    ChangeVolumeSoundMem(255 * Volume / 100, WalkSEHandle);
}