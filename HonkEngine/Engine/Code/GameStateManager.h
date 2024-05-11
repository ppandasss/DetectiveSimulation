// GameStateManager.h
#pragma once
#include <iostream>
#include <functional>
#include <map>
#include "Application.h"
#include "GameObjects/BellManager.h"
#include "Audio/AudioManager.h"

enum GameState {
    ROOM1_STATE,
    ROOM2_STATE,
    ROOM3_STATE,
    ROOM4_STATE,
    Ending
};

enum RoomState {
    Order,
    Prepare,
    Serve,
    Score,
    MealReact,
    Inspection,
    End,
};

std::string gameStateNameToDoorName(GameState state) {
    switch (state) {
    case GameState::ROOM1_STATE:
        return "Room1Door";
    case GameState::ROOM2_STATE:
        return "Room2Door";
    case GameState::ROOM3_STATE:
        return "Room3Door";
    case GameState::ROOM4_STATE:
        return "Room4Door";
    default:
        return ""; // Default empty if no match found
    }
}

class GameStateManager {

private:
    static GameStateManager* instance;
    GameState currentGameState = GameState::ROOM1_STATE;
    RoomState currentRoomState = RoomState::Order;

    std::map<std::pair<GameState, RoomState>, std::function<void()>> stateActions;

    GameStateManager() {

        // Define actions for each state transition 

        //ROOM1
        // 
        //Prepare
        stateActions[std::make_pair(GameState::ROOM1_STATE, RoomState::Prepare)] = []() {

            DoorManager::GetInstance().GetDoorByName("Room1Door")->setPermission(false);
            DoorManager::GetInstance().GetDoorByName("KitchenDoor")->setPermission(true);
            Timer::GetInstance().start(120);
            Application::Get().SetScene("Hallway");
            AudioManager::GetInstance().PlaySound("slideDoor");
            std::cout << "Transition to Room1 Prepare state." << std::endl;
         };
        
        //Serve
        stateActions[std::make_pair(GameState::ROOM1_STATE, RoomState::Serve)] = []() {
           
		};

        stateActions[std::make_pair(GameState::ROOM1_STATE, RoomState::Inspection)] = []() {
            //Application::Get().SetScene("Hallway");
            //AudioManager::GetInstance().PlaySound("slideDoor");
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
