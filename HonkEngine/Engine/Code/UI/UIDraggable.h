#pragma once

#include "../UI/UIElement.h"

class UIDraggable : public UIElement {

public:

    UIDraggable(const std::string& name, const std::string& texturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen)
        : UIElement(name, texturePath, position, scale, isOnScreen) {

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

    void setDragBounds(const glm::vec2& TopLeft, const glm::vec2& BottomRight) {

        minBound = TopLeft;
        maxBound = BottomRight;

    }

    void setDragBoundsByObject(const glm::vec3& position, const glm::vec3& scale) {

        // Calculate the top left and bottom right corners of the object based on its position and scale
        glm::vec2 objectTopLeft = glm::vec2(position.x - scale.x / 2.0f, position.y - scale.y / 2.0f);
        glm::vec2 objectBottomRight = glm::vec2(position.x + scale.x / 2.0f, position.y + scale.y / 2.0f);

        // Set the drag bounds using the calculated corners
        setDragBounds(objectTopLeft, objectBottomRight);

    }


    bool isWithinDragBounds(const glm::vec3& position) {

        // Calculate the bounds of the sprite based on its position and scale
        float leftEdge = position.x - (m_scale.x / 2.0f);
        float rightEdge = position.x + (m_scale.x / 2.0f);
        float topEdge = position.y - (m_scale.y / 2.0f);
        float bottomEdge = position.y + (m_scale.y / 2.0f);

        return (leftEdge >= minBound.x && rightEdge <= maxBound.x &&
            topEdge >= minBound.y && bottomEdge <= maxBound.y);

    }

    glm::vec3 snapToBoundaries(const glm::vec3& position) {

        float leftEdge = position.x - (m_scale.x / 2.0f);
        float rightEdge = position.x + (m_scale.x / 2.0f);
        float topEdge = position.y - (m_scale.y / 2.0f);
        float bottomEdge = position.y + (m_scale.y / 2.0f);

        // Clamp the position to the nearest valid position within the boundaries
        float newX = glm::clamp(position.x, minBound.x + (m_scale.x / 2.0f), maxBound.x - (m_scale.x / 2.0f));
        float newY = glm::clamp(position.y, minBound.y + (m_scale.y / 2.0f), maxBound.y - (m_scale.y / 2.0f));

        return glm::vec3(newX, newY, position.z);
    }


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

            glm::vec2 mouseDelta = mouseWorldPos - dragStartPos;
            glm::vec3 newPosition = glm::vec3(dragStartPos, 0.0f) + glm::vec3(mouseDelta, 0.0f) + glm::vec3(dragOffset, 0.0f);

            // Check if the new position is within the boundaries
            if (isWithinDragBounds(newPosition)) {
                m_position = newPosition;
            } else {
                // If the new position is outside the boundaries, snap it back
                m_position = snapToBoundaries(newPosition);
            }


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

    glm::vec2 minBound = glm::vec2(-4.0f, -3.0f); //top - left corner
    glm::vec2 maxBound = glm::vec2(4.0f, 3.0f); //bottom - right corner

};