// GameStateManager.h
#pragma once
#include <iostream>
#include <functional>
#include <map>
#include "Application.h"
#include "GameObjects/BellManager.h"
#include "Audio/AudioManager.h"
#include "GameObjects/DoorManager.h"
#include "GameObjects/Timer.h"
#include "GameObjects/BellManager.h"

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
            Timer::GetInstance().stop();
            };

        //End   
        stateActions[std::make_pair(GameState::ROOM1_STATE, RoomState::End)] = []() {
            DoorManager::GetInstance().GetDoorByName("Room1Door")->setPermission(true);  // Allow exit
            AudioManager::GetInstance().PlaySound("slideDoor");
            // Optionally stop room-specific music
            Application::Get().SetTimer(3000, []() {
                Application::Get().SetScene("Hallway");  // Transition to another scene
                }, false);
            GameStateManager::GetInstance().SetGameState(GameState::ROOM2_STATE);  // Move to the next game state if applicable
            GameStateManager::GetInstance().SetRoomState(RoomState::Order);  // Move to the next room state if applicable
            };

      //ROOM2

        
        
        
        
        

 
    }


public:

    static GameStateManager& GetInstance() {
        if (!instance) {
            instance = new GameStateManager();
        }
        return *instance;
    }

    void setupOrderStateActions() {
     
    }


    void setupPrepareStateActions() {
        //Room 1
        
    }

    void setupServeStateActions() {
        //Room 1
        
    }

    void setupEndStateActions() {
        //Room 1
       

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
