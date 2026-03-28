

#include "KeyFrame.h"


KeyFrame::KeyFrame(float k, VECTOR r) : key(k), rot(r)
{

}

KeyFrame::~KeyFrame()
{

}

void KeyFrame::SetFrame(float k, VECTOR r)
{
    key = k;
    rot = r;
}