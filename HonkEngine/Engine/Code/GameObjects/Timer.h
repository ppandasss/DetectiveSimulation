#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include "../Text/Text.h"
#include "../UI/UIElement.h"  // Ensure you have included the correct path for UIElement

class Timer {
public:
    using TimerObserver = std::function<void()>;

    // Correct constructor definition without the class name prefix
    Timer() : isRunning(false), audioManager(AudioManager::GetInstance()) {
        UpdateTimerUIVisibility();  // Update UI visibility at initialization
        audioManager.LoadSound("timerTicking", "Assets/Sounds/SFX_TimerTicking.mp3", 0.75f);
    }

    static Timer& GetInstance() {
        static Timer instance;
        return instance;
    }

    void Initialize(Text* countdownText) {
        this->countdownText = countdownText;
        UpdateTimerUIVisibility();  // Update UI visibility at initialization
    }

    void AddObserver(TimerObserver observer) {
        observers.push_back(observer);
    }

    void SetTimerUI(UIElement* timerUI) {
        this->timerUI = timerUI;
        std::cout << "Timer UI set in scene: " << (timerUI ? "Set" : "Not Set") << std::endl;
    }

    void UpdateTimerUIVisibility() {
        if (timerUI) {
            std::cout << "Timer UI update: isRunning = " << isRunning << ", activeStatus = " << timerUI->getActiveStatus() << std::endl;
            timerUI->setActiveStatus(isRunning);
        }
        else {
            std::cout << "Timer UI is not set." << std::endl;
        }
    }

    void start(int durationInSeconds) {
        if (!isRunning) {
            endTime = std::chrono::steady_clock::now() + std::chrono::seconds(durationInSeconds);
            lastUpdateTime = std::chrono::steady_clock::now();
            isRunning = true;
            if (timerUI) {
                timerUI->setActiveStatus(true);  // Directly set to true when starting
            }
            NotifyObservers();
            audioManager.PlaySound("timerTicking", true);
        }
    }

    void stop() {
        if (isRunning) {
            isRunning = false;
            if (timerUI) {
                timerUI->setActiveStatus(false);  // Directly set to false when stopping
            }
            NotifyObservers();
            audioManager.StopSound("timerTicking");
        }
    }


    void Update(float dt) {
        if (isRunning) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastUpdateTime).count() > 0) {
                lastUpdateTime = now;
                if (getRemainingTime() <= 0) {
                    stop();
                }
                NotifyObservers();
            }
        }
    }

    int getRemainingTime() const {
        if (isRunning) {
            auto now = std::chrono::steady_clock::now();
            auto remainingTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - now).count();
            return remainingTime;
        }
        return 0;
    }

    void updateCountdownDisplay() {
        if (countdownText) {
            int remainingTime = getRemainingTime();
            int minutes = remainingTime / 60;
            int seconds = remainingTime % 60;
            countdownText->SetContent(std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
        }
    }

    bool isTimerRunning() const {
        return isRunning;
    }

    std::string GetTime() {
        int remainingTime = getRemainingTime();
        int minutes = remainingTime / 60;
        int seconds = remainingTime % 60;
        return std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
    }

    // Notify all observers about a change
    void NotifyObservers() {
        for (auto& observer : observers) {
            observer();
        }
        updateCountdownDisplay();
    }

   

    bool GetTimerUIVisibility() {
        return this->timerUI->getActiveStatus();
    }

private:
    std::vector<TimerObserver> observers;
    std::chrono::time_point<std::chrono::steady_clock> endTime, lastUpdateTime;
    bool isRunning = false;
    Text* countdownText = nullptr;
    UIElement* timerUI = nullptr; // UI Element to show/hide based on the timer status
    AudioManager& audioManager;
};
