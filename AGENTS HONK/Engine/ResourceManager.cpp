#include <ResourceManager.h>

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager()
{
    // Clean up loaded textures
    for (auto& pair : TexturesVector)
    {
        delete pair.second;
    }
    TexturesVector.clear();

    // Clean up created meshes
    for (CDTMesh* mesh : MeshesVector)
    {
        delete mesh;
    }
    MeshesVector.clear();
}

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

CDTTex* ResourceManager::SetTexture(const std::string& fileName)
{
    if (TexturesVector.find(fileName) != TexturesVector.end())
    {
        return TexturesVector[fileName];
    }

    CDTTex* pTex = new CDTTex();
    *pTex = TextureLoad(fileName.c_str());

    TexturesVector[fileName] = pTex;

    return pTex;
}

CDTMesh* ResourceManager::CreateMeshVertices(int spriteSheetWidth, int spriteSheetHeight)
{
    CDTMesh* pMesh = new CDTMesh();
    std::vector<CDTVertex> vertices;
    CDTVertex v1, v2, v3, v4;

    float uvStepX = 1.0f / spriteSheetWidth;
    float uvStepY = 1.0f / spriteSheetHeight;

    vertices.clear();
    v1.x = -0.5f; v1.y = -0.5f; v1.z = 0.0f; v1.r = 1.0f; v1.g = 0.0f; v1.b = 0.0f; v1.u = 0.0f; v1.v = 0.0f;
    v2.x = 0.5f; v2.y = -0.5f; v2.z = 0.0f; v2.r = 0.0f; v2.g = 1.0f; v2.b = 0.0f; v2.u = uvStepX; v2.v = 0.0f;
    v3.x = 0.5f; v3.y = 0.5f; v3.z = 0.0f; v3.r = 0.0f; v3.g = 0.0f; v3.b = 1.0f; v3.u = uvStepX; v3.v = uvStepY;
    v4.x = -0.5f; v4.y = 0.5f; v4.z = 0.0f; v4.r = 1.0f; v4.g = 1.0f; v4.b = 0.0f; v4.u = 0.0f; v4.v = uvStepY;
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v1);
    vertices.push_back(v3);
    vertices.push_back(v4);

    *pMesh = CreateMesh(vertices);
    MeshesVector.push_back(pMesh);

    return pMesh;
}

void ResourceManager::Clean()
{
    // Clean up resources when needed, e.g., during application shutdown

    // Clean up textures
    for (auto& pair : TexturesVector)
    {
        if (pair.second != nullptr)
        {
            TextureUnload(*pair.second);
            delete pair.second;
        }
    }
    TexturesVector.clear();

    // Clean up meshes
    for (auto& mesh : MeshesVector)
    {
        if (mesh != nullptr)
        {
            UnloadMesh(*mesh);
            delete mesh;
        }
    }
    MeshesVector.clear();
}