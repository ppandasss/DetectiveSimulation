// GameStateManager.h
#pragma once
#include <iostream>
#include <functional>
#include <map>
#include "Application.h"
#include "GameObjects/BellManager.h"
#include "Audio/AudioManager.h"

enum struct GameState {
    Room1,
    Room2,
    Room3,
    Room4,
    End
};

enum struct RoomState {
    Order,
    Prepare,
    Serve,
    Inspection
};

class GameStateManager {

private:
    static GameStateManager* instance;
    GameState currentState;
    RoomState currentRoomState;
    std::map<std::pair<GameState, RoomState>, std::function<void()>> stateEntryActions;
    std::map<GameState, RoomState> lastRoomState;
    BellManager bellManager = BellManager::GetInstance();

    GameStateManager() : currentState(GameState::Room1), currentRoomState(RoomState::Order) {

    }


public:

    static GameStateManager& GetInstance() {
        static GameStateManager instance;
        return instance;
    }

    void setGameState(GameState state) {
        currentState = state;
        executeRoomStateAction();  
    }

    void setRoomState(RoomState state) {
        if (currentRoomState != state) {
            currentRoomState = state;
            executeRoomStateAction();  
        }
    }


    GameState getGameState() const {
        return currentState;
    }

    void executeRoomStateAction() {
        auto statePair = std::make_pair(currentState, currentRoomState);
        // Execute only if this state hasn't been set before or is transitioning
        if (lastRoomState[currentState] != currentRoomState) {
            if (stateEntryActions.find(statePair) != stateEntryActions.end()) {
                stateEntryActions[statePair]();
            }
            lastRoomState[currentState] = currentRoomState; 
        }
    }

    RoomState getRoomState() const {
        return currentRoomState;
    }

    void Update(float dt, long frame) {
        // Here you can handle continuous checks or updates needed for the current state
        
    }
};

GameStateManager* GameStateManager::instance = nullptr;
