#pragma once

#include <vector>
#include "Door.h"
#include <functional>
#include <iostream>
#include <string>


class DoorManager {
public:

    static DoorManager& GetInstance()
    {
        static DoorManager instance;
        return instance;
    }
    void AddDoor(Door* door)
    {
      doors.push_back(door);
    }
    bool CheckDoorCollisions(const glm::vec3& playerPosition, const glm::vec3& playerScale, const std::function<void(Door*)>& onDoorCollision) {
        bool collisionDetected = false;
        for (auto& door : doors) {
            if (door->CheckCollision(playerPosition, playerScale)) {
                door->Highlight(true);
                onDoorCollision(door); // Now passing the door object directly
                collisionDetected = true;
            }
            else {
                door->Highlight(false);
            }
        }
        return collisionDetected;
    }
    std::string CheckDoorCollisionsAndGetRoom(const glm::vec3& playerPosition, const glm::vec3& playerScale) {
        for (auto& door : doors) {
            if (door->CheckCollision(playerPosition, playerScale)) {
                door->Highlight(true);
                return door->GetSceneName(); // Return the name of the room for the first door collision detected
            }
            else {
                door->Highlight(false);
            }
        }
        return ""; // Return an empty string if no collision
    }

    Door* GetDoorByName(const std::string& name) {
        for (auto* door : doors) {
            //std::cout << "Checking door: " << door->GetName() << " against " << name << std::endl;
            if (door->GetName() == name) {
                return door;
            }
        }
        return nullptr;
    }



private:
    DoorManager() = default;
    std::vector<Door*> doors;
};

