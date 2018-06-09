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

    GLuint textureObj;

    struct Vertex
    {
        glm::vec3 Position;
        glm::vec2 UVCoord;
    };

    void LoadResources()
    {
        // glm::vec3 vertices[3];
        // vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f); // bottom-left
        // vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);  // bottom-right
        // vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);   // top-center

        Vertex vertices[] = {
            { glm::vec3(-1.0f, -1.0f, 0.0f),  glm::vec2(0.0f, 0.0f) },
            { glm::vec3(1.0f, -1.0f, 0.0f),   glm::vec2(1.0f, 0.0f) },
            { glm::vec3(0.0f, 1.0f, 0.0f),    glm::vec2(0.5f, 1.0f) }
        };


        glGenBuffers(1, &mVertexBufferObj);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObj);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // TEXTURE LOADING
        SDL_Surface *surface = SDL_LoadBMP("textura.bmp");
        std::cout << "Texture loaded with " << surface->w << " x " << surface->h << std::endl;

        // uint32_t pixels[] = {
        //     0xFFFFFFFF,
        //     0xFFFFFFFF,
        //     0xFFFFFFFF,
        //     0xFFFFFFFF,
        // };        

        glGenTextures(1, &textureObj);
        glBindTexture(GL_TEXTURE_2D, textureObj);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
    }

    void Render()
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObj);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12); // offset=12=3vertices*4bytes
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureObj);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
};