#define WIN_WIDTH  800
#define WIN_HEIGHT 600
#define NAME    "Ticking Tea Pang Cha"



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Application.h"

#include "Game/LevelScene.h"
#include "Game/Room1.h"
#include <iostream>




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



int main()
{
   Application game(WIN_WIDTH, WIN_HEIGHT, NAME);

    game.AddScene("start", new LevelScene());
    game.SetScene("start");
    game.AddScene("room1", new Room1());

    game.Run();

    return 0;


}
