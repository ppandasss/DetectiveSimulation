#pragma once
#include "GameObject.h"
#include "UIElement.h"
#include "UIButton.h"
#include <vector>

class UIManager :public GameObject{

	
	public:
		UIManager();
		void RenderUI() {

			// Render UI elements
			for (UIElement* element : uiElements) {
				element->Render();
			}

		}

		// Handle mouse clicks for UI elements
		void HandleMouseClick(int x, int y) {

			//loop through all UI in vector and check if the element is clickable and if theres a point inside
			//call onClick function of that UI if true

			for (UIElement* element : uiElements) {
				if (element->IsClickable() && element->IsPointInside(x, y)) {
					element->OnClick();
				}
			}

		}


		void Update(float dt, long frame) {

			Input& input = Application::GetInput();

			// Update UI elements
			for (UIElement* element : uiElements) {
				element->Update(dt, frame);
			}

			if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1))
			{
				mousePos = Application::Get().CursorPos();
				HandleMouseClick(mousePos.x, mousePos.y);
				//std::cout << "x: " << mousePos.x << " y: " << mousePos.y << std::endl;
			}
			

		}
	

	
	private:
		std::vector<UIElement*> uiElements;

		//pushback all UI Elements being used into vector/ to initialize when game begins
		void CreateUIElement() {

			uiElements.push_back(new UIButton("Button 1", "Assets/Images/konrai.jpg", 4.0f, 4.0f);

		}
		glm::vec2 mousePos;
	
};