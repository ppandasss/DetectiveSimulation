#pragma once

#include <vector>
#include "Door.h"
#include <functional>


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
    void CheckDoorCollisions(const glm::vec3& playerPosition, const glm::vec3& playerScale, const std::function<void(const std::string&)>& onDoorCollision)
    {
        for (const auto& door : doors) {
            if (door->CheckCollision(playerPosition, playerScale)) {
                onDoorCollision(door->GetSceneName());
                break;
            }
        }
    }

private:
    DoorManager() = default;
    std::vector<Door*> doors;
};

