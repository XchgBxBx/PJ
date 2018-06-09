//
// Scene.h
//
// 2018-05-23
//

#pragma once

#include "Node.h"

class Scene
{
protected:
public:
    Scene();
    ~Scene();

    virtual void LoadResources();
    virtual void Update();
    virtual void Render();
};