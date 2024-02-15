#pragma once

#include <vector>
#include <functional>
#include <string>
#include <map>

class EventManager{

    public:
        using EventListener = std::function<void(const std::string&)>; // Basic listener signature
        using EventListeners = std::vector<EventListener>;

        static void Subscribe(const std::string& eventType, EventListener listener) {
            listeners[eventType].push_back(listener);
        }

        static void Emit(const std::string& eventType, const std::string& eventData) {

            auto& subs = listeners[eventType];
            for (auto& listener : subs) {
                listener(eventData); // Pass event-specific data to the listener
            }

        }

    private:
        static std::map<std::string, EventListeners> listeners; // Maps event types to their listeners


};