#pragma once
#pragma once

#include "Scene.h"

class LoadScene : public Scene
{
public:
    LoadScene();
    virtual ~LoadScene();

    void Initialize(void) override;
    void Uninitialize(void) override;
    Scene* Update(void) override;
    void LateUpdate(void) override;
    void Render(void) override;

private:
    int GraphHandle2;
};