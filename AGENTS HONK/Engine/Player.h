//Player.h
#pragma once
#include<Object/GameObject.h>

class Player : public  GameObject {

public:
    Player(Properties* props);

    // Override the GameObject's virtual functions
    void Draw() override;
    void Update(float dt) override;
    void Clean() override;

    // Additional methods for player-specific behavior
  

private:
    // Add any player-specific properties or variables here
    float playerSpeed = 20.0f;
};