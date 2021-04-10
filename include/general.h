#pragma once
#include "core.h"
#include "graphics.h"
#include "entities.h"
#include <iostream>
#include <algorithm>

class Player : public Object
{
private:
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        boost::serialization::base_object<Object>(*this);
    }
    //
    //Width of the camera control zone in pixels
    int borderWidth = 40;
    //Pointer to the current window
    sf::RenderWindow* window;
public:
    Entity* selectedUnit = nullptr;
    Player() = default;
    explicit Player(sf::RenderWindow& wind)
    {
        window = &wind;
        this->AddComponent(CameraComponent(wind));
    }

    void OnStart() override;
    void OnTick() override;
};
