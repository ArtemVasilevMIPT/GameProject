//
// Created by marcille on 06.03.2021.
//

#include "../include/graphics.h"
#include <iostream>

SpriteComponent::SpriteComponent(std::string texturePath)
{
    name = "SpriteComponent";
    if(!texture.loadFromFile(texturePath))
    {
        std::cerr << "Failed to load texture from path: " << texturePath << std::endl;
        return;
    }
}

void SpriteComponent::SetTexture(sf::Texture& tex)
{
    texture = tex;
}

const sf::Texture &SpriteComponent::GetTexture() const
{
    return texture;
}

sf::Sprite SpriteComponent::GetSprite() const
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(spritePosition.first, spritePosition.second);
    return sprite;
}

void SpriteComponent::SetPosition(float x, float y)
{
    spritePosition.first = x;
    spritePosition.second = y;
}

const std::pair<float, float>& SpriteComponent::GetPosition()
{
    return spritePosition;
}

Camera::Camera(sf::RenderWindow &window)
{
    view = window.getDefaultView();
}
