#pragma once

#include <vector>
#include "Engine.h"
#include <glm/glm.hpp>
#include "../GameObjects/Gameobject.h"
#include "../GameObjects/RenderGameObject.h"
#include "UIElement.h"
#include "UIButton.h"


class UIManager{

	
	public:
		UIManager(){

			CreateUIElements();
		
		}
		
		/*
		* 
		void RenderUI(){

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

		*/


		void Update(float dt, long frame) {

			
			

		}

		~UIManager() {

			for (UIElement* element : uiElements) {
				delete element;
			}

			uiElements.clear();  //Clear the vector
		}
	

	
	private:
		std::vector<UIElement*> uiElements;

		glm::vec2 mousePos;

		//pushback all UI Elements being used into vector/ to initialize when game begins
		void CreateUIElements() {

			uiElements.push_back(new UIButton("Button 1", "Assets/Images/journalticket.jpg", glm::vec2(0.0f, 0.0f), glm::vec2(4.0f, 4.0f), UIElement::IN_GAME));

		}	
	
};