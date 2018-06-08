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
#include <glm/gtc/matrix_transform.hpp>

class Node
{
public:
    GLuint  mVertexBufferObj = 0;
    GLuint  mIndexBufferObj = 0;

    glm::vec3 mPosition = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 mRotation = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 mScale = glm::vec3(1.0f,1.0f,1.0f);

    glm::mat4 mModel = glm::mat4(1.0f);
    
    Node();
    ~Node();

    virtual void LoadResources();
    virtual void Update();
    virtual void Render();
};
