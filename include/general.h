#pragma once
#include "core.h"
#include "graphics.h"
#include "entities.h"
#include <iostream>
#include <algorithm>

class Player : public Object
{
private:
    //Width of the camera control zone in pixels
    int borderWidth = 40;
    //Pointer to the current window
    sf::RenderWindow* window;
public:
    Unit* selectedUnit = nullptr;
    explicit Player(sf::RenderWindow& wind)
    {
        window = &wind;
        this->AddComponent(CameraComponent(wind));
    }

    void OnStart() override;
    void OnTick() override;
};

