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
#include "Scene/Room3.h"
#include "Scene/Room4.h"
#include "Scene/Kitchen.h"
#include "Scene/LoadScene.h"
#include "Scene/MainMenu.h"
#include "Scene/JournalEntry.h"
#include "Scene/EndScene.h"
#include "Scene/OpenScene.h"
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
    game.AddScene("Room3", new Room3());
    game.AddScene("Room4", new Room4());
    game.AddScene("Kitchen", new Kitchen());
    game.AddScene("MainMenu", new MainMenu()); 
    game.AddScene("OpenScene", new OpenScene());
    game.AddScene("JournalEntry", new JournalEntry());
    game.AddScene("EndScene", new EndScene());
    game.SetScene("LoadScene");



    //Run game
    game.Run();

    return 0;


}