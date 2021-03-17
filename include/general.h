#pragma once
#include "core.h"
#include "graphics.h"

class Player : public Object
{
private:
    //Width of the camera control zone in pixels
    int borderWidth = 40;
    sf::RenderWindow* window;
public:
    explicit Player(sf::RenderWindow& wind)
    {
        window = &wind;
        this->AddComponent(CameraComponent(wind));
    }

    void OnStart() override;
    void OnTick() override;
};

