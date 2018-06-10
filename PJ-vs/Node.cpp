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

void Node::ConvertMatrix(const aiMatrix4x4& from, glm::mat4& to)
{
    to[0][0] = from.a1; to[0][1] = from.b1; to[0][2] = from.c1; to[0][3] = from.d1;
    to[1][0] = from.a2; to[1][1] = from.b2; to[1][2] = from.c2; to[1][3] = from.d2;
    to[2][0] = from.a3; to[2][1] = from.b3; to[2][2] = from.c3; to[2][3] = from.d3;
    to[3][0] = from.a4; to[3][1] = from.b4; to[3][2] = from.c4; to[3][3] = from.d4;
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

        // ROOT Inverse
        glm::mat4 globalInverse;
        ConvertMatrix(scene->mRootNode->mTransformation, globalInverse);
        globalInverse = glm::inverse(globalInverse);

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

            // load bone data NOW
            if (aMesh->HasBones())
            {
                LoadBones(aMesh, meshes.size() - 1);
            }
        }
    }
    else
    {
        std::cout << "error loading scene" << std::endl;
        system("pause");
        exit(0);
    }
}

void Node::LoadBones(const aiMesh* mesh, unsigned int meshIndex)
{
    std::map<std::string, unsigned int> boneMapping;
    unsigned int boneCount = 0;
    std::vector<BoneInfo> boneInfos;
    std::vector<BoneVertexData> bones;
    bones.resize(mesh->mNumVertices);

    for (unsigned int i = 0; i < mesh->mNumBones; i++)
    {
        unsigned int boneIndex = 0;
        std::string boneName(mesh->mBones[i]->mName.data);

        if (boneMapping.find(boneName) == boneMapping.end())
        {
            boneIndex = boneCount;
            boneCount++;

            BoneInfo info;
            glm::mat4 offset;
            ConvertMatrix(mesh->mBones[i]->mOffsetMatrix, offset);
            info.BoneOffset = offset;
            boneInfos.push_back(info);

            boneMapping[boneName] = boneIndex;
        }
        else
        {
            boneIndex = boneMapping[boneName];
        }

        for (unsigned int w = 0; w < mesh->mBones[i]->mNumWeights; w++)
        {
            // TODO: figure out reference's base vertex(it's used for VAO??)
            unsigned int vertexId = mesh->mBones[i]->mWeights[w].mVertexId;
            float weight = mesh->mBones[i]->mWeights[w].mWeight;

            // TODO: change that hardcoded number 3 vvvvvvv
            for (unsigned int j = 0; j <= 3; j++)
            {
                if (bones[vertexId].Weights[j] == 0.0)
                {
                    bones[vertexId].BoneIds[j] = boneIndex;
                    bones[vertexId].Weights[j] = weight;
                    break;
                }
            }

            // TODO:correct verification
            /*std::cout << "MORE BONES THAN EXPECTED" << std::endl;
            system("pause");
            exit(0);*/
        }
    }

    meshes[meshIndex].LoadBoneData(bones);
}