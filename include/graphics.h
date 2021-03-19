//
// Created by marcille on 06.03.2021.
//

#pragma once
#include "core.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

//Basic component that stores sprite and texture of an object
class SpriteComponent : public Component
{
private:
    sf::Texture texture;
public:
    std::pair<float, float> spritePosition;
    SpriteComponent()
    {
        name = "SpriteComponent";
        spritePosition = std::make_pair<float, float>(0.0f, 0.0f);
    }
    SpriteComponent(const SpriteComponent& other) = default;
    SpriteComponent(std::string texturePath);
    ~SpriteComponent() = default;

    //Sets new texture to an object
    void SetTexture(sf::Texture& tex);
    //Sets position of a sprite on screen
    void SetPosition(float x, float y);
    //Returns reference to an object's texture
    const sf::Texture& GetTexture() const;
    //Returns reference to an object's sprite
    sf::Sprite GetSprite() const; 

    const std::pair<float, float>& GetPosition();
};

//Camera object
class Camera
{
private:
    sf::View view;

public:
    Camera() = delete;
    ~Camera() = default;
    Camera(const Camera& other) = default;
    Camera(sf::RenderWindow& window);


    const sf::View& GetView()
    {
        return view;
    }

    void SetView(sf::View& v)
    {
        view = v;
    }

    //Shifts current camera view by vector with given coordinates
    void move(float x, float y)
    {
        view.move(sf::Vector2f(x, y));
    }

    //Zooms current camera view by given factor
    void zoom(float factor)
    {
        view.zoom(factor);
    }
};

//Component that controls camera
class CameraComponent : public Component
{
private:
    Camera cam;
    float flySpeed = 0.9f;
    float zoomSpeed = 0.9f;

public:
    CameraComponent(sf::RenderWindow& window, float fSpeed = 0.9f, float zSpeed = 0.9f)
    : cam(window),
      flySpeed(fSpeed),
      zoomSpeed(zSpeed)
    {
        name = "CameraComponent";
    }
    CameraComponent(const CameraComponent& other) = default;
    ~CameraComponent() = default;

    Camera& GetCamera()
    {
        return cam;
    }

    void SetCamera(Camera& c)
    {
        cam = c;
    }
    //Shifts position of the camera by given vector
    void moveCamera(float x, float y)
    {
        cam.move(x * flySpeed, y * flySpeed);
    }
    //Changes zoom of the camera by given factor
    void zoomCamera(float factor)
    {
        cam.zoom(factor * zoomSpeed);
    }
};
