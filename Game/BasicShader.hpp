//
// BasicShader.hpp
//
// 2018-05-24
//

#pragma once

#include "../Shader.h"

class BasicShader: public Shader
{
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
        uniforms["gWorld"] = glGetUniformLocation(mShaderProgramID, "gWorld");
    }

    void Activate()
    {
        Shader::Activate();
    }
};