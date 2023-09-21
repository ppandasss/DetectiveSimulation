#pragma once

#include <map>
#include <string>
#include "Scene.h"

class SceneManager {
public:
    SceneManager(int win_width,int win_height);
    ~SceneManager();

    void AddScene(const std::string& name, Scene* scene);
    void SetScene(const std::string& name);
    void Run();  // This will contain the game loop

private:
    Scene* m_currentScene;
    std::map<std::string, Scene*> m_sceneMap;
};
