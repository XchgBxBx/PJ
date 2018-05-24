//
// TestScene.hpp
//
// 2018-05-23
//

#pragma once

#include "../Scene.h"
#include "../Shader.h"

#include "Quad.hpp"
#include "Dot.hpp"

class TestScene: public Scene
{
private:
    Shader  mShader;

    Quad    mQuad;
    Dot     mDot;
public:
    void LoadResources()
    {
        //Initialize clear color
        glClearColor(0.3f, 0.3f, 0.3f, 1.f);

        mShader.LoadShader();

        mQuad.LoadResources();
        mDot.LoadResources();
    }

    void Render()
    {
        mShader.Activate();
        mQuad.Render(mShader.GetAttrib());
        mShader.Deactivate();

        mDot.Render();
    }
};
