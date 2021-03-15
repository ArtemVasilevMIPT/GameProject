#include "general.h"

void Player::OnStart()
{

}

void Player::OnTick()
{
    //Camera control
    sf::Vector2i cursorPosition = sf::Mouse::getPosition(*window);
    sf::Vector2u windowSize = window->getSize();
    sf::Vector2f viewSize = window->getView().getSize();
    sf::Vector2f viewCenter = window->getView().getCenter();
    float offX = 0.f, offY = 0.f;
    if(cursorPosition.x < borderWidth && viewCenter.x > viewSize.x / 2)
    {
        --offX;
    }
    else if(cursorPosition.x > windowSize.x - borderWidth && viewCenter.x < windowSize.x - viewSize.x / 2)
    {
        ++offX;
    }
    if(cursorPosition.y < borderWidth && viewCenter.y > viewSize.y / 2)
    {
        --offY;
    }
    else if(cursorPosition.y > windowSize.y - borderWidth && viewCenter.y < windowSize.y - viewSize.y / 2)
    {
        ++offY;
    }
    this->GetComponent<CameraComponent>()->moveCamera(offX, offY);
    //
}