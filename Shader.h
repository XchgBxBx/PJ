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
#include <map>

class Shader
{
protected:
    GLuint  mShaderProgramID = 0;
    
    const char* ReadFileContents(const char* path);

public:

    Shader();
    ~Shader();

    std::map<std::string, GLint> uniforms;

    void LoadShader();
    
    virtual void PostInitialization();

    virtual void Activate();
    virtual void Deactivate();

    virtual const char* GetVertexShaderSource();
    virtual const char* GetFragmentShaderSource();
};