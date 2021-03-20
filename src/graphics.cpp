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
    spriteSize = std::make_pair(texture.getSize().x, texture.getSize().y);
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
    sprite.setRotation(spriteRotation);
    sprite.setScale(spriteSize.first / texture.getSize().x, spriteSize.second / texture.getSize().y);
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

void SpriteComponent::SetRotation(float angle)
{
    spriteRotation = angle;
}

float SpriteComponent::GetRotation() const
{
    return spriteRotation;
}

void SpriteComponent::SetSize(float width, float height)
{
    spriteSize.first = width;
    spriteSize.second = height;
}

std::pair<float, float> SpriteComponent::GetSize() const
{
    return spriteSize;
}

Camera::Camera(sf::RenderWindow &window)
{
    view = window.getDefaultView();
}
