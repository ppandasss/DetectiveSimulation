#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <CDT.h>

class ResourceManager
{
public:
    static ResourceManager& GetInstance();

    CDTTex* SetTexture(const std::string& fileName);
    CDTMesh* CreateMeshVertices(int spriteSheetWidth, int spriteSheetHeight);
    void Clean();

private:
    ResourceManager();
    ~ResourceManager();

    std::map<std::string, CDTTex*> TexturesVector;
    std::vector<CDTMesh*> MeshesVector;
};
