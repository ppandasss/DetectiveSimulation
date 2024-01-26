#pragma once

#include "../UI/UIElement.h"

class UIDraggable : public UIElement {

public:
    UIDraggable(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale)
        : UIElement(name, texturePath, position, scale) {

        //category = UIcategory;
        isDragging = false;

    }


    void OnClick() {

        //DRAG OBJECT HERE 

        std::cout << "Draggable Clicked" << std::endl;
        isDragging = true;


    }

 
    void Update(float dt, long frame) override {

        
        Input& input = Application::GetInput();
        RenderGameObject::Update(dt, frame);

        CurrentMousePos = Application::Get().CursorPos();

        if (input.Get().GetMouseButtonUp(GLFW_MOUSE_BUTTON_1)) {

            isDragging = false;
            //std::cout << "DRAGGABLE RELEASED" << std::endl;

        }

        if (IsClickable()) {

            //std::cout << "DRAGGABLE CLICK" << std::endl;

            if (IsPointInside(CurrentMousePos.x, CurrentMousePos.y)) {

                //std::cout << "DRAGGABLE POINT" << std::endl;

                if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {

                    OnClick();
                    isDragging = true;
                    dragStartPos = CurrentMousePos; // Capture the starting point of the drag

                    dragOffset = glm::vec2(m_position.x, m_position.y) - MousetoScreen(CurrentMousePos.x, CurrentMousePos.y); // Offset between mouse and object position

                }

            
            }
        }

        
        if (isDragging) {

            /*

            // Continue drag - Update object position
            glm::vec2 mouseDelta = MousetoScreen(CurrentMousePos.x, CurrentMousePos.y) - dragStartPos; // Apply offset to maintain relative position under cursor

            //glm::vec2 convertedPosition = MousetoScreen(newUiPosition.x, newUiPosition.y);
            m_position = glm::vec3(dragStartPos, 0.0f) + glm::vec3(mouseDelta, 0.0f) + glm::vec3(dragOffset, 0.0f);

            */

            glm::vec2 worldMousePos = MousetoScreen(CurrentMousePos.x, CurrentMousePos.y);

            m_position = glm::vec3(worldMousePos, 0.0f);
            

        }

    }

private:

    glm::vec2 CurrentMousePos;
    glm::vec2 dragStartPos;
    bool isDragging;

    glm::vec2 dragOffset; // Offset between

};