//
// BasicShader.hpp
//
// 2018-05-24
//

#pragma once

#include "../Shader.h"

class BasicShader: public Shader
{
private:
    GLint mScaleUniform;

public:
    const char* GetVertexShaderSource()
    {
        return ReadFileContents("Shaders/3DBasicVS.glsl");
    }

    const char* GetFragmentShaderSource()
    {
        return ReadFileContents("Shaders/3DBasicFS.glsl");
    }

    void PostInitialization()
    {
        mScaleUniform = glGetUniformLocation(mShaderProgramID, "gScale");
    }

    void Activate()
    {
        Shader::Activate();
        glUniform1f(mScaleUniform, 0.25f);
    }
};