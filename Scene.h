//
// Scene.h
//
// 2018-05-23
//

#ifndef _SCENE_H_
#define _SCENE_H_

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

#endif //_GAME_H_