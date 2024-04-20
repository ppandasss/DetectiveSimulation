#pragma once

#include <string>
#include "../Text/Text.h"
#include <functional>
#include <vector>
#include "../UI/UIElement.h"

class OrderData {
public:

    using OrderDataObserver = std::function<void()>;

    static OrderData& GetInstance() {
        static OrderData instance; // Singleton instance
        return instance;
    }

    void Initialize(Text* orderNoText, Text* teaOrderText, Text* sandwichOrderText, Text* pastryOrderText) {
        this->orderNoText = orderNoText;
        this->teaOrderText = teaOrderText;
        this->sandwichOrderText = sandwichOrderText;
        this->pastryOrderText = pastryOrderText;
    }

    void AddObserver(OrderDataObserver observer) {
        observers.push_back(observer);
    }

    void SetOrderPaper(UIElement* orderPaper) {
        this->orderPaper = orderPaper;
        UpdateOrderPaperVisibility();
    }

    void UpdateOrderPaperVisibility() {
        if (orderPaper) {
            orderPaper->setActiveStatus(IsValidOrder());
        }
    }

    // Notify all observers about a change
    void NotifyObservers() {
        for (auto& observer : observers) {
            observer();
        }
        UpdateOrderPaperVisibility();
    }

   

    void SetRoomNumber(const std::string& roomNumber) {
        this->roomNumber = roomNumber;
        if (orderNoText) {
            orderNoText->SetContent(roomNumber);
        }
        NotifyObservers();
    }

    void SetTeaOrder(const std::string& teaOrder) {
        this->teaOrder = teaOrder;
        if (teaOrderText) {
            teaOrderText->SetContent(teaOrder);
        }
        NotifyObservers();
    }

    void SetSandwichOrder(const std::string& sandwichOrder) {
        this->sandwichOrder = sandwichOrder;
        if (sandwichOrderText) {
            sandwichOrderText->SetContent(sandwichOrder);
        }
        NotifyObservers();
    }

    void SetPastryOrder(const std::string& pastryOrder) {
        this->pastryOrder = pastryOrder;
        if (pastryOrderText) {
            pastryOrderText->SetContent(pastryOrder);
        }
        NotifyObservers();
    }

    const std::string& GetRoomNumber() const {
        return roomNumber;
    }

    const std::string& GetTeaOrder() const {
        return teaOrder;
    }

    const std::string& GetSandwichOrder() const {
        return sandwichOrder;
    }

    const std::string& GetPastryOrder() const {
        return pastryOrder;
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

    std::string roomNumber;
    std::string teaOrder;
    std::string sandwichOrder;
    std::string pastryOrder;

    OrderData() = default; // Private constructor for singleton
    std::vector<OrderDataObserver> observers;


    UIElement* orderPaper = nullptr;
    Text* orderNoText = nullptr;
    Text* teaOrderText = nullptr;
    Text* sandwichOrderText = nullptr;
    Text* pastryOrderText = nullptr;


};
