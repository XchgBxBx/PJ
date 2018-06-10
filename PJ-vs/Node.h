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

#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 UVCoord;
};

struct Mesh
{
    GLuint vertexBuffer;
    GLuint indexBuffer;

    unsigned int numIndices;

    void LoadData(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    {
        numIndices = indices.size();

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);

        std::cout << "mesh loaded" << std::endl;
    }
};

class Node
{
public:

    std::vector<Mesh> meshes;

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

    void LoadMesh(std::string filename);
};
