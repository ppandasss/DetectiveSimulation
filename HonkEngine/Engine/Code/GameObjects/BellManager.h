#pragma once

#include <vector>
#include "Bell.h"
#include "DoorManager.h"
#include <functional>
#include <iostream>
#include <string>

class BellManager {
public:
    static BellManager& GetInstance() {
        static BellManager instance;
        return instance;
    }

    void AddBell(Bell* bell, Door* linkedDoor) {
        bells.push_back(bell);
        linkedDoors.push_back(linkedDoor);
    }

    void StartRinging(std::string bellName) {

        for (size_t i = 0; i < bells.size(); i++) {
			Bell* bell = bells[i];
			if (bell->getName() == bellName) {
				bell->startRinging();
			}
		}

	}

    Bell* getBell(const std::string& bellName) {
        for (size_t i = 0; i < bells.size(); i++) {
            Bell* bell = bells[i];
            if (bell->getName() == bellName) {
                return bell;
            }
        }
        return nullptr;  // Return nullptr if no bell found
    }

    void Update(float dt,float frame) {
        for (size_t i = 0; i < bells.size(); i++) {
            Bell* bell = bells[i];
            Door* door = linkedDoors[i];
            bell->Update(dt,frame);
            if (bell->isBellRinging() && door) {
                door->setPermission(true);
            }
        }
    }

    void StopAllRinging() {
        for (auto* bell : bells) {
          bell->stopRinging();
        }
    }



private:
    std::vector<Bell*> bells;
    std::vector<Door*> linkedDoors;

    BellManager() = default; // Constructor is private to ensure it's a singleton
};
