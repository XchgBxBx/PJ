//
// Shader.cpp
//
// 2018-05-23
//

#include "Shader.h"

#include <iostream>
#include <windows.h>

Shader::Shader()
{

}

Shader::~Shader()
{

}

void Shader::LoadShader()
{
    std::cout << "initializing shaders" << std::endl;

    mShaderProgramID = glCreateProgram();

    ///
    // VertexShader
    ///

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar* vertexShaderSource[1];
    vertexShaderSource[0] = GetVertexShaderSource();

    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

    glCompileShader(vertexShader);

    GLint vsCompileResult = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vsCompileResult);
    if (vsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't compile vertex shader" << std::endl;
        exit(0);
    }

    // attach

    glAttachShader(mShaderProgramID, vertexShader);


    ///
    // Fragment Shader
    ///

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragShaderSource[1];
    fragShaderSource[0] = GetFragmentShaderSource();

    glShaderSource(fragShader, 1, fragShaderSource, NULL);

    glCompileShader(fragShader);

    GLint fsCompileResult = GL_FALSE;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fsCompileResult);
    if (fsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't compile fragment shader" << std::endl;
        exit(0);
    }

    // attach
    glAttachShader(mShaderProgramID, fragShader);


    ///
    // Linking
    ///

    glLinkProgram(mShaderProgramID);
    GLint linkingResult = GL_FALSE;
    glGetShaderiv(mShaderProgramID, GL_LINK_STATUS, &linkingResult);
    if (fsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't link shader" << std::endl;
        exit(0);
    }

    mVertexPos2DLoc = glGetAttribLocation(mShaderProgramID, "LVertexPos2D");
    if (mVertexPos2DLoc == -1)
    {
        std::cout << "bad variable name" << std::endl;
        exit(0);
    }
}

void Shader::Activate()
{
    glUseProgram(mShaderProgramID);
    glEnableVertexAttribArray(mVertexPos2DLoc);
}

void Shader::Deactivate()
{
    glDisableVertexAttribArray(mVertexPos2DLoc);
    glUseProgram(NULL);
}

const char* Shader::GetVertexShaderSource()
{
    return "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }";
}

const char* Shader::GetFragmentShaderSource()
{
    return  "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 0.0, 1.0, 1.0 ); }";
}
