//
// Dot.hpp
//
// 2018-05-23
//

#ifndef _DOT_HPP_
#define _DOT_HPP_

#include "../Node.h"

class Dot: public Node
{
public:
    void LoadResources()
    {
        glm::vec3 vertices[1];

        vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);
        glGenBuffers(1, &mVertexBufferObj);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObj);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

    void Render()
    {
        glEnableVertexAttribArray(0); // fixed pipeline
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObj);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_POINTS, 0, 1);
        glDisableVertexAttribArray(0); // fixed pipeline
    }
};

#endif // _DOT_HPP_