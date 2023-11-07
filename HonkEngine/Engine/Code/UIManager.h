#pragma once
#include "GameObject.h"
#include "UIElement.h"
#include <vector>

class UIManager :public GameObject{

	
	public:
		UIManager();
		void RenderUI();//render UI that need to be displayed currently
		void Update(float dt, long frame) override; //loop throught elements vector and call update
		void HandleMouseClick(int x, int y); 
		//loop through all UI in vector and check if the element is clickable and if theres a point inside
		//call onClick function of that UI if true

	
	private:
		std::vector<UIElement*> uiElements;
		void CreateUIElement(); //pushback all UI Elements being used into vector/ to initialize when game game begins
		
	
};