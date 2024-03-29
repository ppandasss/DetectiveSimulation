#pragma once

#include "../UI/UIElement.h"

class UIDraggable : public UIElement {

public:
    /*UIDraggable(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen, glm::vec3 snapToPos)
        : UIElement(name, texturePath, position, scale,isOnScreen) {

        //category = UIcategory;
        isDragging = false;
        originalPosition = position;
        snapToPosition = snapToPos;

    }*/

    UIDraggable(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen)
        : UIElement(name, texturePath, position, scale, isOnScreen) {

        //category = UIcategory;
        isDragging = false;
        originalPosition = position;

    }


    void OnClick() {

        //DRAG OBJECT HERE 

        std::cout << "Draggable Clicked" << std::endl;
        isDragging = true;


    }

    //Method to set the click action
    virtual void SetOnReleaseAction(const std::function<void()>& action) {
        onReleaseAction = action;
    }



    void onRelease() {

        if (onReleaseAction) {
            onReleaseAction();
        }


    }

    bool withinRage(glm::vec3 targetPosition, float threshold) {

        glm::vec2 releasePosition = Application::Get().MousetoWorld();

        float distance = glm::distance(glm::vec3(releasePosition.x, releasePosition.y, 0.0f), targetPosition);
        return distance <= threshold;

    }

    /*void snapUIPosition(glm::vec3 uiPos) {

        if (withinRage(uiPos, snapToPosition, snapThreshold)) {
            m_position = snapToPosition;
        }
        else {
            m_position = originalPosition;
        }

    }*/

    void snapBack() {
        m_position = originalPosition;
    }


    void Update(float dt, long frame) override {


        Input& input = Application::GetInput();
        UIElement::Update(dt, frame);

        //mousePos = Application::Get().CursorPos();
        mouseWorldPos = Application::Get().MousetoWorld();

        if (IsClickable()) {

            //std::cout << "DRAGGABLE CLICK" << std::endl;

            if (IsPointInside(mouseWorldPos.x, mouseWorldPos.y)) {

                if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {

                    OnClick();
                    isDragging = true;
                    dragStartPos = mouseWorldPos; // Capture the starting point of the drag
                    dragOffset = glm::vec2(m_position.x, m_position.y) - mouseWorldPos; // Offset between mouse and object position

                }

            }
        }


        if (isDragging) {
            // Continue drag - Update object position
            glm::vec2 mouseDelta = mouseWorldPos - dragStartPos; // Use the already converted mouseWorldPos
            m_position = glm::vec3(dragStartPos, 0.0f) + glm::vec3(mouseDelta, 0.0f) + glm::vec3(dragOffset, 0.0f);


            //Mouse click released
            if (input.Get().GetMouseButtonUp(GLFW_MOUSE_BUTTON_1)) {

                isDragging = false;
                std::cout << "DRAGGABLE RELEASED" << std::endl;

                //snapUIPosition(m_position);
                snapBack();

                onRelease();

            }

        }

    }

private:

    glm::vec2 mousePos;
    glm::vec2 mouseWorldPos;

    glm::vec2 dragStartPos;
    bool isDragging;
    glm::vec2 dragOffset; // Offset between

    //snap to position variables
    glm::vec3 originalPosition; //position at instantiation
    glm::vec3 snapToPosition;
    float snapThreshold = 8.0f;

    std::function<void()> onReleaseAction;

};