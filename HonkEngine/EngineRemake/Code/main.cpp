// ---------------------------------------------------------------------------
// Goal:		game state managment demo with framerate
// Usage:		press S to step between each frame
//				press R to restart the level
//				press N to change the level
//				press esc to quit
// ---------------------------------------------------------------------------


// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>


// Include GLEW
#include <glad/glad.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "system.h"
#include "CDT.h"
#include"SceneManager.h"
#include"Scene.h"



// windows
int		win_width = 1400;
int		win_height = 1050;


int main(void) {

	System system;
	// Initialize the System (GFW, GLEW, Input, Create window)
	SceneManager sceneManager(win_width,win_height);

	sceneManager.AddScene("Level1", new Scene());
	sceneManager.SetScene("Level1");
	sceneManager.Run();


	return 0;
}

