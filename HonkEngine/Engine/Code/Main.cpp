#define WIN_WIDTH  1920
#define WIN_HEIGHT 1080
#define NAME    "Ticking Tea Pang Cha"



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Shader.h"
#include "Application.h"

#include "Scene/Hallway.h"
#include "Scene/Room1.h"
#include "Scene/Room2.h"
#include "Scene/Kitchen.h"
#include "Scene/LoadScene.h"
#include <iostream>




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



int main()
{
    Application game(WIN_WIDTH, WIN_HEIGHT, NAME);

    //Add scene
    game.AddScene("LoadScene", new LoadScene());
    //Set start scene

    game.AddScene("Hallway", new Hallway());
    game.AddScene("Room1", new Room1());
    game.AddScene("Room2", new Room2());
    game.AddScene("Kitchen", new Kitchen());
    game.SetScene("LoadScene");



    //Run game
    game.Run();

    return 0;


}