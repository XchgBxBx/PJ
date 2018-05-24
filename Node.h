//
// Node.h
//
// 2018-05-23
//

#pragma once

// TODO: move headers to one single file
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <glm/glm.hpp>

class Node
{
protected:
    GLuint  mVertexBufferObj = 0;
    GLuint  mIndexBufferObj = 0;

public:
    Node();
    ~Node();

    void LoadResources();
    void Update();
    void Render(GLuint programAttrib);
};
