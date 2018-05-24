//
// Node.cpp
//
// 2018-05-23
//

#include "Node.h"

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
