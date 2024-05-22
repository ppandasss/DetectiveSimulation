#pragma once

#include <map>
#include <stack>
#include <memory>

#include "../PopupWidget/Interface.h"

enum InterfaceType {
    OPTIONS,
    EXIT
};

class InterfaceManager {

public:

    static InterfaceManager& getInstance() {
        static InterfaceManager instance;  // Guaranteed to be destroyed and instantiated on first use.
        return instance;
    }

    InterfaceManager(const InterfaceManager&) = delete;             // Delete copy constructor
    InterfaceManager& operator=(const InterfaceManager&) = delete;  // Delete copy assignment operator

    void ActivateInterface(InterfaceType interface) {

        auto it = interfaces.find(interface);

        if (it != interfaces.end()) {
            if (!activeInterfaces.empty()) {
                // Optionally deactivate the top interface
                activeInterfaces.top()->setActiveStatus(false);

            }

            activeInterfaces.push(it->second);
            it->second->setActiveStatus(true);

        }

    }

    void closeCurrentInterface() {

        if (!activeInterfaces.empty()) {

            activeInterfaces.top()->setActiveStatus(false);
            activeInterfaces.pop();

            if (!activeInterfaces.empty()) {
                // Reactivate the new top interface
                activeInterfaces.top()->setActiveStatus(true);

            }
        }
    }

    void closeAllInterfaces() {

        while (!activeInterfaces.empty()) {

            activeInterfaces.top()->setActiveStatus(false);
            activeInterfaces.pop();

        }

    }

    void AddInterface(InterfaceType type, Interface* interface) {
        // Wrap the raw pointer in a shared_ptr with a no-op deleter

        interface->setActiveStatus(false);
        interfaces[type] = std::shared_ptr<Interface>(interface, [](Interface*) {});

    }


private:

    InterfaceManager() {}


    //store all interfaces in the game
    std::map<InterfaceType, std::shared_ptr<Interface>> interfaces;


    //store active interfaces
    std::stack<std::shared_ptr<Interface>> activeInterfaces;

};