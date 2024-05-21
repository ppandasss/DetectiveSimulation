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
#include "GameObjects/OrderData.h"

#define PREPARE_DURATION 5  //in seconds


enum GameState {
    ROOM1_STATE,
    ROOM2_STATE,
    ROOM3_STATE,
    ROOM4_STATE,
    END_STATE
};

enum RoomState {
    Order,
    Prepare,
    Serve,
    Score,
    MealReact,
    InspectionStart,
    Inspection,
    InspectionEnd,
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
    GameState currentGameState = GameState::ROOM3_STATE;
    RoomState currentRoomState = RoomState::Order;

    std::map<std::pair<GameState, RoomState>, std::function<void()>> stateActions;

    GameStateManager() {

       

        //--------------------------------ROOM1---------------------------   
        
        //Prepare
        stateActions[std::make_pair(GameState::ROOM1_STATE, RoomState::Prepare)] = []() {

            DoorManager::GetInstance().GetDoorByName("Room1Door")->setPermission(false);
            DoorManager::GetInstance().GetDoorByName("KitchenDoor")->setPermission(true);
            Timer::GetInstance().start(PREPARE_DURATION);
            Application::Get().SetScene("Hallway");
            AudioManager::GetInstance().PlaySound("slideDoor");
            std::cout << "Transition to Room1 Prepare state." << std::endl;
            };

        //Serve
        stateActions[std::make_pair(GameState::ROOM1_STATE, RoomState::Serve)] = []() {
            Timer::GetInstance().stop();
            OrderData::GetInstance().ClearOrder();
            std::cout << "Transition to Room1 Serve state." << std::endl;
            };

        //End   
        stateActions[std::make_pair(GameState::ROOM1_STATE, RoomState::End)] = []() {
            DoorManager::GetInstance().GetDoorByName("Room1Door")->setPermission(false);  // Allow exit
            AudioManager::GetInstance().PlaySound("slideDoor");
            // Optionally stop room-specific music
            Application::Get().SetTimer(3000, []() {
                Application::Get().SetScene("Hallway");  // Transition to another scene
                }, false);
            GameStateManager::GetInstance().SetGameState(GameState::ROOM3_STATE);  // Move to the next game state if applicable
            GameStateManager::GetInstance().SetRoomState(RoomState::Order);
            std::cout << "Transition to Room1 End state." << std::endl;
            };

        //-----------------------------ROOM2-------------------------------   
        
        //Prepare
        stateActions[std::make_pair(GameState::ROOM2_STATE, RoomState::Prepare)] = []() {

            DoorManager::GetInstance().GetDoorByName("Room2Door")->setPermission(false);
            DoorManager::GetInstance().GetDoorByName("KitchenDoor")->setPermission(true);
            Timer::GetInstance().start(PREPARE_DURATION);
            Application::Get().SetScene("Hallway");
            AudioManager::GetInstance().PlaySound("slideDoor");
            std::cout << "Transition to Room2 Prepare state." << std::endl;
            };

        //Serve
        stateActions[std::make_pair(GameState::ROOM2_STATE, RoomState::Serve)] = []() {
            Timer::GetInstance().stop();
            OrderData::GetInstance().ClearOrder();
            std::cout << "Transition to Room2 Serve state." << std::endl;
         };


        //End
        stateActions[std::make_pair(GameState::ROOM2_STATE, RoomState::End)] = []() {
            DoorManager::GetInstance().GetDoorByName("Room2Door")->setPermission(false);  // Allow exit
            AudioManager::GetInstance().PlaySound("slideDoor");
            // Optionally stop room-specific music
            Application::Get().SetTimer(3000, []() {
                Application::Get().SetScene("Hallway");  // Transition to another scene
                }, false);
            GameStateManager::GetInstance().SetGameState(GameState::ROOM4_STATE);  // Move to the next game state if applicable
            GameStateManager::GetInstance().SetRoomState(RoomState::Order);  // Move to the next room state if applicable
            };

        //-----------------------------ROOM3---------------------------   
        
        //Prepare
        stateActions[std::make_pair(GameState::ROOM3_STATE, RoomState::Prepare)] = []() {

            DoorManager::GetInstance().GetDoorByName("Room3Door")->setPermission(false);
            DoorManager::GetInstance().GetDoorByName("KitchenDoor")->setPermission(true);
            Timer::GetInstance().start(PREPARE_DURATION);
            Application::Get().SetScene("Hallway");
            AudioManager::GetInstance().PlaySound("slideDoor");
            std::cout << "Transition to Room3 Prepare state." << std::endl;
            };

        //Serve
        stateActions[std::make_pair(GameState::ROOM3_STATE, RoomState::Serve)] = []() {
            Timer::GetInstance().stop();
            OrderData::GetInstance().ClearOrder();
            std::cout << "Transition to Room3 Serve state." << std::endl;
         };

         //End
        stateActions[std::make_pair(GameState::ROOM3_STATE, RoomState::End)] = []() {
            DoorManager::GetInstance().GetDoorByName("Room3Door")->setPermission(false);  // Allow exit
            AudioManager::GetInstance().PlaySound("slideDoor");
            // Optionally stop room-specific music
            Application::Get().SetTimer(3000, []() {
                Application::Get().SetScene("Hallway");  // Transition to another scene
                }, false);
            GameStateManager::GetInstance().SetGameState(GameState::ROOM2_STATE); 
            GameStateManager::GetInstance().SetRoomState(RoomState::Order);
            };
      
        //-----------------------------ROOM4---------------------------   

        //Prepare
        stateActions[std::make_pair(GameState::ROOM4_STATE, RoomState::Prepare)] = []() {

            DoorManager::GetInstance().GetDoorByName("Room4Door")->setPermission(false);
            DoorManager::GetInstance().GetDoorByName("KitchenDoor")->setPermission(true);
            Timer::GetInstance().start(PREPARE_DURATION);
            Application::Get().SetScene("Hallway");
            AudioManager::GetInstance().PlaySound("slideDoor");
            std::cout << "Transition to Room4 Prepare state." << std::endl;
            };

        //Serve
        stateActions[std::make_pair(GameState::ROOM4_STATE, RoomState::Serve)] = []() {
            Timer::GetInstance().stop();
            OrderData::GetInstance().ClearOrder();
            std::cout << "Transition to Room4 Serve state." << std::endl;
            };

        //End
        stateActions[std::make_pair(GameState::ROOM4_STATE, RoomState::End)] = []() {
            DoorManager::GetInstance().GetDoorByName("Room4Door")->setPermission(false);  // Allow exit
            AudioManager::GetInstance().PlaySound("slideDoor");
            // Optionally stop room-specific music
            Application::Get().SetTimer(3000, []() {
                Application::Get().SetScene("Hallway");  // Transition to another scene
                }, false);
            GameStateManager::GetInstance().SetGameState(GameState::END_STATE);
            GameStateManager::GetInstance().SetRoomState(RoomState::End);  // Move to the next room state if applicable

           };
        

        //-----------------------------END---------------------------

        stateActions[std::make_pair(GameState::END_STATE, RoomState::End)] = []() {
 
            //End cutscene 

        };

 
    }


public:

    static GameStateManager& GetInstance() {
        if (!instance) {
            instance = new GameStateManager();
        }
        return *instance;
    }
    void Update() {
       HandleTimerExpiration();
	}

    void HandleTimerExpiration() {
        if (currentRoomState == RoomState::Prepare && Timer::GetInstance().isTimesUp() && !BellManager::GetInstance().isAnyBellRinging()) {
            switch (currentGameState) {
            case GameState::ROOM1_STATE:
                BellManager::GetInstance().getBell("bellCabin1")->startRinging();
                break;
            case GameState::ROOM2_STATE:
                BellManager::GetInstance().getBell("bellCabin2")->startRinging();
                break;
            case GameState::ROOM3_STATE:
                BellManager::GetInstance().getBell("bellCabin3")->startRinging();
                break;
            case GameState::ROOM4_STATE:
                BellManager::GetInstance().getBell("bellCabin4")->startRinging();
                break;
            default:
                break;
            }
        }
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
