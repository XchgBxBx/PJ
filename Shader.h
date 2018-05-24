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
    GLint   mVertexPos2DLoc = -1;
public:
    Shader();
    ~Shader();

    void LoadShader();
    void Activate();
    void Deactivate();

    const char* GetVertexShaderSource();
    const char* GetFragmentShaderSource();
};