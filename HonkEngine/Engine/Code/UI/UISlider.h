#pragma once

#include "../UI/UIElement.h"

enum SliderType {
    MasterVolume,
    SFXVolume,
    MusicVolume
};

class UISlider : public UIElement {

public:

	UISlider(const std::string& name, const std::string& knobTexturePath, const glm::vec3 position, const glm::vec3 scale, bool isOnScreen, SliderType type)
		: UIElement(name, knobTexturePath, position, scale, isOnScreen), sliderType(type) {

        // Instantiate the background and fill bar
        background = new UIObject("SliderBackground", "Assets/Images/Interface/Slider_Background.png", position, isOnScreen);
        background->SetScale(glm::vec3(3.0f, 0.3f, 0.0f));

        // Calculate min and max values based on the fill bar's position and scale
        minValue = position.x - background->GetScale().x / 2.0f;
        maxValue = position.x + background->GetScale().x / 2.0f;

        //fillBar = new UIObject("SliderFill", "Assets/Images/Interface/Slider_Background.png", glm::vec3(position.x - scale.x / 2.0f, position.y, position.z), isOnScreen);
        //fillBar->SetScale(glm::vec3(0.0f, scale.y, scale.z));  // Initial scale

        UpdateKnobPosition();

	}

    void OnClick() {

        //std::cout << "Draggable Clicked" << std::endl;
        isDragging = true;

    }

    void Render() override {
        background->Render();
        UIElement::Render();
    }

    void Update(float dt, long frame) override {

        UIElement::Update(dt, frame);
        Input& input = Application::GetInput();

        mouseWorldPos = Application::Get().MousetoWorld();

        if (IsClickable() && IsPointInside(mouseWorldPos.x, mouseWorldPos.y)) {
            if (input.Get().GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
                
                OnClick();

                dragStartPos = mouseWorldPos; // Capture the starting point of the drag
                dragOffset = glm::vec2(m_position.x, m_position.y) - mouseWorldPos; // Offset between mouse and object position

            }  

        }
        

        if (isDragging) {

            glm::vec2 mouseDelta = mouseWorldPos - dragStartPos;
            glm::vec3 newPosition = glm::vec3(dragStartPos, 0.0f) + glm::vec3(mouseDelta, 0.0f) + glm::vec3(dragOffset, 0.0f);

            glm::vec3 newHorizontalPos = glm::vec3(newPosition.x, m_position.y, 0.0f);

            if (isWithinDragBounds(newHorizontalPos)) {
                m_position = newHorizontalPos;

                float newValue = (newPosition.x - minValue) / (maxValue - minValue);
                SetValue(newValue);

            }
            else {
                // If the new position is outside the boundaries, snap it back
                m_position = snapToBoundaries(newHorizontalPos);
            }
        

            if (input.Get().GetMouseButtonUp(GLFW_MOUSE_BUTTON_1)) {
                isDragging = false;

                
            }

        }

        background->Update(dt, frame);
    }

    void SetValue(float value) {
        this->value = std::min(maxValue, std::max(minValue, value));
        if (onValueChanged) {
            onValueChanged(value);
        }
    }

    void SetOnValueChangedCallback(std::function<void(float)> callback) {
        onValueChanged = callback;
    }

    bool isWithinDragBounds(const glm::vec3& position) {
        // Ensure the knob stays within the horizontal bounds based on the knob's center position
        return (position.x >= minValue && position.x <= maxValue);
    }

    glm::vec3 snapToBoundaries(const glm::vec3& position) {
        // Snap the knob to the nearest valid position within the horizontal boundaries
        float newX = glm::clamp(position.x, minValue, maxValue);
        return glm::vec3(newX, m_position.y, m_position.z);
    }


    void UpdateKnobPosition() {
        float volume = 0.0f;
        switch (sliderType) {
        case MasterVolume:
            volume = AudioManager::GetInstance().GetMasterVolume();
            break;
        case SFXVolume:
            volume = AudioManager::GetInstance().GetSFXVolumeMultiplier();
            break;
        case MusicVolume:
            volume = AudioManager::GetInstance().GetMusicVolumeMultiplier();
            break;
        }
        SetValue(volume);
        m_position.x = minValue + (volume * (maxValue - minValue));
    }



private:

    glm::vec2 mousePos;
    glm::vec2 mouseWorldPos;

    float minValue;
    float maxValue;
    float value;
    bool isDragging = false;

    UIObject* background;
    UIObject* fillBar;
    std::function<void(float)> onValueChanged;

    glm::vec2 dragStartPos;
    bool isHover = false;
    glm::vec2 dragOffset; 

    SliderType sliderType;

};

