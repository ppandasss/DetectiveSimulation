#pragma once

#include "Scene.h"
#include "../GameObjects/RenderGameObject.h"
#include"../GameObjects/AnimateGameObject.h"	

#include "../GameObjects/Player.h"
#include "../Text/TextRenderer.h"
#include "../Text/Text.h"
#include"../Audio/AudioManager.h"	
#include "../UI/UIButton.h"
#include "../UI/UIDraggable.h"
#include "../UI/UINormal.h"
#include "../UI/UIElement.h"
#include "../GameObjects/Book.h"
#include "../UI/UIButtonEmpty.h"
#include "../GameObjects/Door.h"
#include "../GameObjects/DoorsManager.h"

class LoadScene : public Scene
{

private:

public:
	LoadScene() 
	{
		GameObject* engineLogo = new RenderGameObject("EngineLogo", "Assets/Images/logo.png");
	}

	void Update(float dt, long frame) {
		Scene::Update(dt, frame); 
		Input& input = Application::GetInput();

		for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
			if (input.Get().GetKey(key)) {
				Application::Get().SetScene("Hallway");
				break; // Exit the loop once a key is detected
			}
		}
	}

};





