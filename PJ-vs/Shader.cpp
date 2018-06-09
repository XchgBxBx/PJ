//
// Shader.cpp
//
// 2018-05-23
//

#include "Shader.h"

#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

Shader::Shader()
{

}

Shader::~Shader()
{

}

void Shader::LoadShader()
{
    std::cout << "loading shader" << std::endl;

    mShaderProgramID = glCreateProgram();

    ///
    // VertexShader
    ///

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string content = GetVertexShaderSource().c_str();
    const char *bufferVertex = content.c_str();

    glShaderSource(vertexShader, 1, &bufferVertex, NULL);

    glCompileShader(vertexShader);

    GLint vsCompileResult = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vsCompileResult);
    if (vsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't compile vertex shader" << std::endl;
        system("pause");exit(0);
    }

    // attach

    glAttachShader(mShaderProgramID, vertexShader);


    ///
    // Fragment Shader
    ///

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    content = GetFragmentShaderSource().c_str();
    const char *bufferFrag = content.c_str();

    glShaderSource(fragShader, 1, &bufferFrag, NULL);

    glCompileShader(fragShader);

    GLint fsCompileResult = GL_FALSE;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fsCompileResult);
    if (fsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't compile fragment shader" << std::endl;
        system("pause");exit(0);
    }

    // attach
    glAttachShader(mShaderProgramID, fragShader);


    ///
    // Linking
    ///

    glLinkProgram(mShaderProgramID);
    GLint linkingResult = GL_FALSE;
    glGetShaderiv(mShaderProgramID, GL_LINK_STATUS, &linkingResult);
    std::cout << "errorShader::" << gluErrorString(glGetError()) << std::endl;
    if (fsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't link shader" << std::endl;
        system("pause");exit(0);
    }

    PostInitialization();

    // mVertexPos2DLoc = glGetAttribLocation(mShaderProgramID, "LVertexPos2D");
    // if (mVertexPos2DLoc == -1)
    // {
    //     std::cout << "bad variable name" << std::endl;
    //     system("pause");exit(0);
    // }
}

void Shader::PostInitialization()
{
    
}

void Shader::Activate()
{
    glUseProgram(mShaderProgramID);
}

void Shader::Deactivate()
{
    glUseProgram(NULL);
}

std::string Shader::ReadFileContents(const char* path)
{
    std::ifstream file;
    file.open(path);
    std::vector<char> contents;

    file.seekg(0, file.end);
    size_t len = file.tellg();
    file.seekg(0, file.beg);

    contents.resize(len);
    file.read(&contents[0], len);

    file.close();

    return contents.data();
}

std::string Shader::GetVertexShaderSource()
{
    return ReadFileContents("Shaders/2DBasicVS.glsl");
}

std::string Shader::GetFragmentShaderSource()
{
    return ReadFileContents("Shaders/2DBasicFS.glsl");
}
