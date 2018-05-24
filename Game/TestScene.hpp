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
#include "Triangle.hpp"

class TestScene: public Scene
{
private:
    Shader  mShader;

    Quad        mQuad;
    Dot         mDot;
    Triangle    mTriangle;
public:
    void LoadResources()
    {
        //Initialize clear color
        glClearColor(0.3f, 0.3f, 0.3f, 1.f);

        mShader.LoadShader();

        mQuad.LoadResources();
        mDot.LoadResources();
        mTriangle.LoadResources();
    }

    void Render()
    {
        // mShader.Activate();
            //mQuad.Render();
        // mShader.Deactivate();

        glEnableVertexAttribArray(0); // activate fixed pipeline
            glColor3f(1.0f, 1.0f, 1.0f);
            mTriangle.Render();
            glColor3f(1.0f, 0.0f, 0.0f);
            mDot.Render();
        glDisableVertexAttribArray(0); // disable fixed pipeline
    }
};
