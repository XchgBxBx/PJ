//
// Animated.hpp
//
// 2018-06-09
//

#pragma once

#include "../Node.h"

class Animated : public Node
{
public:

    GLuint textureObj;

    void LoadResources()
    {
        LoadMesh("Res/anim.dae");

        // TEXTURE LOADING
        SDL_Surface *surface = SDL_LoadBMP("Res/tex.bmp");
        std::cout << "Texture loaded with " << surface->w << " x " << surface->h << std::endl;    

        glGenTextures(1, &textureObj);
        glBindTexture(GL_TEXTURE_2D, textureObj);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void Render()
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glBindBuffer(GL_ARRAY_BUFFER, meshes[0].vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12); // offset=12=3vertices*4bytes

        glBindBuffer(GL_ARRAY_BUFFER, meshes[0].boneBuffer);
        glVertexAttribIPointer(2, 3, GL_INT, sizeof(BoneVertexData), 0);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(BoneVertexData), (const void*)12); // offset=12=3boneIds*4bytes

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureObj);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[0].indexBuffer);
        glDrawElements(GL_TRIANGLES, meshes[0].numIndices, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
    }
};