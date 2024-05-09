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
    MealReact,
    Score,
    Inspection
};

std::string gameStateNameToDoorName(GameState state) {
    switch (state) {
    case GameState::Room1:
        return "Room1Door";
    case GameState::Room2:
        return "Room2Door";
    case GameState::Room3:
        return "Room3Door";
    case GameState::Room4:
        return "Room4Door";
    default:
        return ""; // Default empty if no match found
    }
}

class GameStateManager {

private:
    static GameStateManager* instance;
    GameState currentGameState = GameState::Room1;
    RoomState currentRoomState = RoomState::Order;

    std::map<std::pair<GameState, RoomState>, std::function<void()>> stateActions;

    GameStateManager() {
        // Define actions for each state transition
        stateActions[std::make_pair(GameState::Room1, RoomState::Prepare)] = []() {

            DoorManager::GetInstance().GetDoorByName("Room1Door")->setPermission(false);
            DoorManager::GetInstance().GetDoorByName("KitchenDoor")->setPermission(true);
            Timer::GetInstance().start(120);
            Application::Get().SetScene("Hallway");
            AudioManager::GetInstance().PlaySound("slideDoor");
            std::cout << "Transition to Room1 Prepare state." << std::endl;
         };
        // Add more state transitions as necessary
        stateActions[std::make_pair(GameState::Room1, RoomState::Serve)] = []() {
            Timer::GetInstance().stop();
		};


 
    }


public:

    static GameStateManager& GetInstance() {
        if (!instance) {
            instance = new GameStateManager();
        }
        return *instance;
    }

    ~GameStateManager() {
        delete instance;
    }

    void SetGameState(GameState state) {
        currentGameState = state;
        ExecuteStateAction();
    }

    void SetRoomState(RoomState state) {
        currentRoomState = state;
        ExecuteStateAction();
    }

    GameState getGameState() const {
        return currentGameState;
    }

    RoomState getRoomState() const {
        return currentRoomState;
    }

    void ExecuteStateAction() {
        auto key = std::make_pair(currentGameState, currentRoomState);
        if (stateActions.find(key) != stateActions.end()) {
            stateActions[key](); // Execute the action associated with the current state
        }
    }
};

GameStateManager* GameStateManager::instance = nullptr;
