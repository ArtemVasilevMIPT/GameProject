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
    return sprite;
}

