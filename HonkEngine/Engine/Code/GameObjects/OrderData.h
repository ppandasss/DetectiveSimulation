#pragma once

#include <string>
#include "../Text/Text.h"

class OrderData {
public:

    static OrderData& GetInstance() {
        static OrderData instance; // Singleton instance
        return instance;
    }

    OrderData(const OrderData&) = delete;
    OrderData& operator=(const OrderData&) = delete;

    void Initialize(Text* orderNoText, Text* teaOrderText, Text* sandwichOrderText, Text* pastryOrderText) {
        this->orderNoText = orderNoText;
        this->teaOrderText = teaOrderText;
        this->sandwichOrderText = sandwichOrderText;
        this->pastryOrderText = pastryOrderText;
     
    }

    void SetRoomNumber(const std::string& roomNumber) {
        this->roomNumber = roomNumber;
        orderNoText->SetContent(roomNumber);
    }

    void SetTeaOrder(const std::string& teaOrder) {
        this->teaOrder = teaOrder;
        teaOrderText->SetContent(teaOrder);
    }

    void SetSandwichOrder(const std::string& sandwichOrder) {
        this->sandwichOrder = sandwichOrder;
        sandwichOrderText->SetContent(sandwichOrder);
    }

    void SetPastryOrder(const std::string& pastryOrder) {
        this->pastryOrder = pastryOrder;
        pastryOrderText->SetContent(pastryOrder);
    }

    bool IsValidOrder() const {
        return !roomNumber.empty() && !teaOrder.empty() && !sandwichOrder.empty() && !pastryOrder.empty();
    }

    void ClearOrder() {
        roomNumber.clear();
        teaOrder.clear();
        sandwichOrder.clear();
        pastryOrder.clear();

        orderNoText->SetContent("");
        teaOrderText->SetContent("");
        sandwichOrderText->SetContent("");
        pastryOrderText->SetContent("");
    }

private:
    OrderData() = default; // Private constructor for singleton

    Text* orderNoText = nullptr;
    Text* teaOrderText = nullptr;
    Text* sandwichOrderText = nullptr;
    Text* pastryOrderText = nullptr;

    std::string roomNumber;
    std::string teaOrder;
    std::string sandwichOrder;
    std::string pastryOrder;
};
