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
    bool CheckDoorCollisions(const glm::vec3& playerPosition, const glm::vec3& playerScale, const std::function<void(const std::string&)>& onDoorCollision) {
        bool collisionDetected = false;
        for (auto& door : doors) {
            if (door->CheckCollision(playerPosition, playerScale)) {
                door->Highlight(true);
                onDoorCollision(door->GetSceneName());
                collisionDetected = true;
            }
            else {
                door->Highlight(false);
            }
        }
        return collisionDetected;
    }


private:
    DoorManager() = default;
    std::vector<Door*> doors;
};

