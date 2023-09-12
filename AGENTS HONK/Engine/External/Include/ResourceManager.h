#pragma once
#include <vector>
#include <string>
#include <map>
#include<iostream>
#include <CDT.h>

class ResourceManager
{
public:
    static ResourceManager& GetInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    // Load a texture based on sprite sheet size and file name
    CDTTex* LoadTexture(const std::string& fileName, int spriteSheetWidth, int spriteSheetHeight);

    // Create a mesh based on sprite sheet size
    CDTMesh* CreateMesh(int spriteSheetWidth, int spriteSheetHeight);

    // Clean up resources
    void Clean();

private:

    ResourceManager() {}

    // Map to store loaded textures
    std::map<std::string, CDTTex*> TexturesVector;
    int numTex;

    // Vector to store created meshes
    std::vector<CDTMesh*> MeshesVector;
    int numMesh;


    // Private functions to load textures and create meshes
    CDTTex* LoadTextureFromFile(const std::string& fileName);
    CDTMesh* CreateMeshFromSpriteSheet(int spriteSheetWidth, int spriteSheetHeight);
};

CDTTex* ResourceManager::LoadTexture(const std::string& fileName, int spriteSheetWidth, int spriteSheetHeight)
{
    // Check if the texture is already loaded
    if (TexturesVector.find(fileName) != TexturesVector.end())
    {
        return TexturesVector[fileName];
    }

    // Load the texture from file
    CDTTex* tex = LoadTextureFromFile(fileName);

    // Store the loaded texture in the map
    TexturesVector[fileName] = tex;

    return tex;
}

CDTMesh* ResourceManager::CreateMesh(int spriteSheetWidth, int spriteSheetHeight)
{
    // Create a new mesh
    CDTMesh* pMesh;
    std::vector<CDTVertex> vertices;
    CDTVertex v1, v2, v3, v4;

    vertices.clear();
    v1.x = -0.5f; v1.y = -0.5f; v1.z = 0.0f; v1.r = 1.0f; v1.g = 0.0f; v1.b = 0.0f; v1.u = 0.0f; v1.v = 0.0f;
    v2.x = 0.5f; v2.y = -0.5f; v2.z = 0.0f; v2.r = 0.0f; v2.g = 1.0f; v2.b = 0.0f; v2.u = 0.25f; v2.v = 0.0f;
    v3.x = 0.5f; v3.y = 0.5f; v3.z = 0.0f; v3.r = 0.0f; v3.g = 0.0f; v3.b = 1.0f; v3.u = 0.25f; v3.v = 0.9f;
    v4.x = -0.5f; v4.y = 0.5f; v4.z = 0.0f; v4.r = 1.0f; v4.g = 1.0f; v4.b = 0.0f; v4.u = 0.0f; v4.v = 0.9f;
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v1);
    vertices.push_back(v3);
    vertices.push_back(v4);

    // Create the mesh and store it in the vector
    pMesh = CreateMesh(vertices);

    // Store the created mesh in the vector
    MeshesVector.push_back(pMesh);

    return pMesh;
}

CDTTex* ResourceManager::LoadTextureFromFile(const std::string& fileName)
{
    // Implement the logic to load a texture from file here
    
    
    // You can use CDTTex's constructor or any other loading method you prefer
    // Return the loaded texture
    return nullptr; // Placeholder, replace with actual loading code
}

CDTMesh* ResourceManager::CreateMeshFromSpriteSheet(int spriteSheetWidth, int spriteSheetHeight)
{
    // Implement the logic to create a mesh based on sprite sheet size here
    // You can use CDTMesh's constructor or any other method you prefer
    // Return the created mesh
    return nullptr; // Placeholder, replace with actual mesh creation code
}

void ResourceManager::Clean()
{
    // Clean up loaded textures
    for (auto& pair : loadedTextures)
    {
        delete pair.second;
    }
    loadedTextures.clear();

    // Clean up created meshes
    for (CDTMesh* mesh : createdMeshes)
    {
        delete mesh;
    }
    createdMeshes.clear();
}

