//
// Shader.h
//
// 2018-05-23
//

#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

class Shader
{
protected:
    GLuint  mShaderProgramID = 0;
    
    const char* ReadFileContents(const char* path);
public:
    Shader();
    ~Shader();

    void LoadShader();
    
    virtual void PostLoading();

    virtual void Activate();
    virtual void Deactivate();

    virtual const char* GetVertexShaderSource();
    virtual const char* GetFragmentShaderSource();
};