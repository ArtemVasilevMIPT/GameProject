#include "general.h"

void Player::OnStart()
{

}

void Player::OnTick()
{
    //Camera control
    sf::Vector2i cursorPosition = sf::Mouse::getPosition(*window);
    int offX = 0, offY = 0;
    if(cursorPosition.x > borderWidth)
    //
}