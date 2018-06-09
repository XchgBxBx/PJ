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
    std::string GetVertexShaderSource()
    {
        return ReadFileContents("Shaders/3DBasicVS.glsl");
    }

    std::string GetFragmentShaderSource()
    {
        return ReadFileContents("Shaders/3DBasicFS.glsl");
    }

    void PostInitialization()
    {
        uniforms["gWorld"] = glGetUniformLocation(mShaderProgramID, "gWorld");
        uniforms["gProjView"] = glGetUniformLocation(mShaderProgramID, "gProjView");
        uniforms["gSampler"] = glGetUniformLocation(mShaderProgramID, "gSampler");
        // TODO: insert assert
    }

    void Activate()
    {
        Shader::Activate();
    }
};