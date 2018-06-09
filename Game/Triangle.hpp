//
// Triangle.hpp
//
// 2018-05-24
//

#pragma once

#include "../Node.h"

class Triangle: public Node
{
public:
    void LoadResources()
    {
        glm::vec3 vertices[3];
        vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f); // bottom-left
        vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);  // bottom-right
        vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);   // top-center

        glGenBuffers(1, &mVertexBufferObj);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObj);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

    void Render()
    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObj);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
    }
};