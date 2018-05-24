//
// Quad.hpp
//
// 2018-05-23
//

#ifndef _QUAD_HPP_
#define _QUAD_HPP_

#include "../Node.h"

class Quad: public Node
{
public:
    void LoadResources()
    {
        //VBO data
        GLfloat vertexData[] =
        {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f
        };

        //IBO data
        GLuint indexData[] = { 0, 1, 2, 3 };

        //Create VBO
        glGenBuffers(1, &mVertexBufferObj);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObj);
        glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

        //Create IBO
        glGenBuffers(1, &mIndexBufferObj);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferObj);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
    }
};



#endif //_QUAD_HPP_