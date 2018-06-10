//
// Node.cpp
//
// 2018-05-23
//

#include "Node.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


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

    mModel = glm::translate(mModel, mPosition);
    
    mModel = glm::rotate(mModel, mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    mModel = glm::rotate(mModel, mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    mModel = glm::rotate(mModel, mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
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

void Node::LoadMesh(std::string filename)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    if (scene)
    {
        std::cout << "numMeshes: " << scene->mNumMeshes << std::endl;
        //meshes.resize(scene->mNumMeshes);
        std::cout << "numMaterials: " << scene->mNumMaterials << std::endl;

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            const aiMesh* aMesh = scene->mMeshes[i];

            std::vector<Vertex> vertices;
            //vertices.resize(aMesh->mNumVertices);
            
            for (unsigned int v = 0; v < aMesh->mNumVertices; v++)
            {
                Vertex vertex{
                    glm::vec3(
                        aMesh->mVertices[v].x,
                        aMesh->mVertices[v].y,
                        aMesh->mVertices[v].z),
                    glm::vec2(
                        aMesh->mTextureCoords[0][v].x,
                        aMesh->mTextureCoords[0][v].y
                    ) };

                vertices.push_back(vertex);
            }

            std::vector<unsigned int> indices;
            //indices.resize(aMesh->mNumFaces);

            for (unsigned int f = 0; f < aMesh->mNumFaces; f++)
            {
                const aiFace& face = aMesh->mFaces[f];

                indices.push_back(face.mIndices[0]);
                indices.push_back(face.mIndices[1]);
                indices.push_back(face.mIndices[2]);
            }

            Mesh mesh;
            mesh.LoadData(vertices, indices);
            meshes.push_back(mesh);
        }
    }
    else
    {
        std::cout << "error loading scene" << std::endl;
        system("pause");
        exit(0);
    }
}