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
#include "BasicShader.hpp"
#include "Animated.hpp"

class TestScene: public Scene
{
private:
    BasicShader m3DShader;

    Triangle    mTriangle;
    Animated    mAnimated;

    glm::mat4   mProjView;
    glm::vec3   mCameraPos = glm::vec3(0.0f, 0.0f, -5.0f);
    glm::vec3   mCameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
public:
    void LoadResources()
    {
        //Initialize clear color
        glClearColor(0.3f, 0.3f, 0.3f, 1.f);

        glEnable(GL_DEPTH_TEST);
        glFrontFace(GL_CW);
        glCullFace(GL_FRONT);
        glEnable(GL_CULL_FACE);
        

        m3DShader.LoadShader();

        mTriangle.LoadResources();
        std::cout << "error::" << gluErrorString(glGetError()) << std::endl;
        mAnimated.LoadResources();
        std::cout << "error::" << gluErrorString(glGetError()) << std::endl;


        // projection-view computation
        // TODO: Aspect-Ratio is hardcoded:
        mProjView = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)
         * glm::lookAt(mCameraPos, mCameraTarget, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void Update()
    {
        //mTriangle.mRotation.y += 0.05f;

        mTriangle.Update();
        mAnimated.mRotation.y += 0.05f;
        mAnimated.mPosition.z += 0.05f;
        mAnimated.Update();
    }

    void Render()
    {
        // mShader.Activate();
            //mQuad.Render();
        // mShader.Deactivate();

        // glEnableVertexAttribArray(0); // activate fixed pipeline
            // glColor3f(1.0f, 1.0f, 1.0f);
            // mTriangle.Render();
            // glColor3f(1.0f, 0.0f, 0.0f);
            // mDot.Render();
        // glDisableVertexAttribArray(0); // disable fixed pipeline

        m3DShader.Activate();
            /*glUniformMatrix4fv(m3DShader.uniforms["gWorld"], 1, GL_FALSE, &mTriangle.mModel[0][0]);
            glUniformMatrix4fv(m3DShader.uniforms["gProjView"], 1, GL_FALSE, &mProjView[0][0]);
            glUniform1i(m3DShader.uniforms["gSampler"], 0);
            mTriangle.Render();*/

            glUniformMatrix4fv(m3DShader.uniforms["gWorld"], 1, GL_FALSE, &mAnimated.mModel[0][0]);
            glUniformMatrix4fv(m3DShader.uniforms["gProjView"], 1, GL_FALSE, &mProjView[0][0]);
            glUniform1i(m3DShader.uniforms["gSampler"], 0);
            mAnimated.Render();
        m3DShader.Deactivate();
    }
};