#pragma once
#include "GameObject.h"
#include "UIElement.h"
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
		void Update(float dt, long frame) {

			// Update UI elements
			for (UIElement* element : uiElements) {
				element->Update(dt, frame);
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
		

	
	private:
		std::vector<UIElement*> uiElements;
		void CreateUIElement(); //pushback all UI Elements being used into vector/ to initialize when game begins
		
	
};