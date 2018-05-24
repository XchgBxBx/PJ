//
// Shader.h
//
// 2018-05-23
//

#ifndef _SHADER_H_
#define _SHADER_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

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
    GLint GetAttrib();
};

#endif //_SHADER_H_