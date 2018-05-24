//
// TestScene.h
//
// 2018-05-23
//

#ifndef _TEST_SCENE_H_
#define _TEST_SCENE_H_

#include "../Scene.h"
#include "../Shader.h"

class TestScene: public Scene
{
private:
    Shader shader;
public:
    void LoadResources();
    void Render();
};


#endif //_TEST_SCENE_H_