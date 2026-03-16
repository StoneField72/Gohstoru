#pragma once

class Sound
{
public:
    Sound();
    virtual ~Sound();

    void Initialize();
    void Uninitialize();
    void Update();

    void PlayBGM(int BGMnum);
    void PlaySE(int SEnum);

    void StopBGM(int BGMnum);
    void StopSE(int SEnum);

    void ChangeBGMVolume(int Volume);
    void ChangeSEVolume(int Volume);

    int GetBGMVolume(){ return BGMVolume; }
     int GetSEVolume(){ return SEVolume; }

private:
    int BGMVolume;
    int SEVolume;

    int ClickSEHandle;
    int ShutterSEHandle;
    int RollSEHandle;
    int LookSEHandle;
    int SommerSEHandle;
    int WindSEHandle;
    int WalkSEHandle;
};
