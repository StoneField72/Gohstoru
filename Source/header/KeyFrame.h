#pragma once


#include "DxLib.h"


class KeyFrame
{
private:
    

public:
    float  key; //キー
    VECTOR rot; //このキーの時の角度

    KeyFrame(float k, VECTOR r);
    virtual ~KeyFrame();

    void SetFrame(float k, VECTOR r);
};