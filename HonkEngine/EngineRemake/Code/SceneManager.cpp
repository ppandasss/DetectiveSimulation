#include "SceneManager.h"
#include "Input.h"
#include "system.h"
SceneManager::SceneManager(int win_width,int win_height) : m_currentScene(nullptr)
{

    SystemInit(win_width, win_height, "Ticking Engine Time");
    CDTInit(win_width, win_height);

}

SceneManager::~SceneManager() {
    // Destructor logic here
}

void SceneManager::AddScene(const std::string& name, Scene* scene) {
    m_sceneMap[name] = scene;
}

void SceneManager::SetScene(const std::string& name) {
    if (m_sceneMap.find(name) != m_sceneMap.end()) {
        m_currentScene = m_sceneMap[name];
    }
}

void SceneManager::Run() {
    // Initialize OpenGL, GLFW, etc.
    // ...
    double lastFrameTime = glfwGetTime();
    double frameRateUpdateInterval = 1.0; // Update frame rate every 1 second
    double frameRateTimer = 0.0;
    int frameCount = 0;

    while (Input::Get().GetKey(GLFW_KEY_ESCAPE)|| glfwWindowShouldClose(window) == 1) {
        double currentTime = glfwGetTime();
        double dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        frameRateTimer += dt;
        frameCount++;

        // Poll events
        // ...

        if (m_currentScene) {
            m_currentScene->Load();
            m_currentScene->Init();
            m_currentScene->Update(dt);
            m_currentScene->Draw();
            m_currentScene->Free();
            m_currentScene->Unload();
        }

        if (frameRateTimer >= frameRateUpdateInterval)
        {
            double frameRate = frameCount / frameRateTimer;
            std::cout << "                                                                                         Frame Rate: " << (int)frameRate << " FPS" << std::endl;
            frameRateTimer = 0.0;
            frameCount = 0;
        }
        // Swap buffers, etc.
        // ...
    }

    // Cleanup
    CDTShutdown();
    SystemShutdown();
    
}
