#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include "../Text/Text.h"
#include "../UI/UIElement.h"  // Ensure you have included the correct path for UIElement

class Timer {
public:
    using TimerObserver = std::function<void()>;

    static Timer& GetInstance() {
        static Timer instance;
        return instance;
    }

    void Initialize(Text* countdownText, UIElement* timerUI) {
        this->countdownText = countdownText;
        this->timerUI = timerUI;
        UpdateTimerUIVisibility();  // Update UI visibility at initialization
    }

    void AddObserver(TimerObserver observer) {
        observers.push_back(observer);
    }

    void start(int durationInSeconds) {
        if (!isRunning) {
            endTime = std::chrono::steady_clock::now() + std::chrono::seconds(durationInSeconds);
            lastUpdateTime = std::chrono::steady_clock::now();
            isRunning = true;
            NotifyObservers();
            UpdateTimerUIVisibility();
        }
    }

    void stop() {
        isRunning = false;
        NotifyObservers();
        UpdateTimerUIVisibility();
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

    // Notify all observers about a change
    void NotifyObservers() {
        for (auto& observer : observers) {
            observer();
        }
        updateCountdownDisplay();
    }

    void UpdateTimerUIVisibility() {
        if (timerUI) {
            timerUI->setActiveStatus(isRunning);
        }
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> endTime, lastUpdateTime;
    bool isRunning = false;
    std::vector<TimerObserver> observers;
    Text* countdownText = nullptr;
    UIElement* timerUI = nullptr; // UI Element to show/hide based on the timer status
};
