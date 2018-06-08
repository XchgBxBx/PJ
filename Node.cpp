//
// Node.cpp
//
// 2018-05-23
//

#include "Node.h"

#include <iostream>

Node::Node()
{

}

Node::~Node()
{

}

void Node::LoadResources()
{

}

void Node::Update()
{
    // scale with IDENTITY
    mModel = glm::scale(glm::mat4(1.0f), mScale);

    mModel = glm::rotate(mModel, mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    mModel = glm::rotate(mModel, mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    mModel = glm::rotate(mModel, mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    mModel = glm::translate(mModel, mPosition);
}

void Node::Render()
{
    //Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObj);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    //Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObj);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
}
