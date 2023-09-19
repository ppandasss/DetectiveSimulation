#include "Application.h"
#include"RenderGameObject.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Application* Application::s_instance = nullptr;

Application::~Application()
{
    std::cout << "Application Desctructor\n";

    for (auto& scene : m_sceneMap)
    {
        delete scene.second;
    }

    glfwTerminate();
}

Application::Application(int win_width, int win_height, const char* title)
{
   

    std::cout << "Application Constructor\n";

    s_instance = this;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(win_width,win_height,title, NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    
    Initialize(SCR_WIDTH,SCR_HEIGHT);



}

void Application::Run()
{
    
    std::cout << "Application Run\n";

    
    //ourShader.setInt("texture2", 1);

    double lastFrameTime = glfwGetTime();
    double frameRateUpdateInterval = 1.0; // Update frame rate every 1 second
    double frameRateTimer = 0.0;
    int frameCount = 0;


    // render loop
    // 
    // -----------
    while (!glfwWindowShouldClose(m_window))
    {

        double currentTime = glfwGetTime();
        double dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        frameRateTimer += dt;
        frameCount++;

        // input
        // -----
        processInput(m_window);


       

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (m_currentScene)
            m_currentScene->Update(dt);



        if (m_currentScene)
            m_currentScene->Render();

        glfwSwapBuffers(m_window);
        glfwPollEvents();

        if (frameRateTimer >= frameRateUpdateInterval)
        {
            double frameRate = frameCount / frameRateTimer;
            std::cout << "                                                                                                          Frame Rate: " << (int)frameRate << " FPS" << std::endl;
            frameRateTimer = 0.0;
            frameCount = 0;
        }
    }

}


