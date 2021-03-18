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
    //Handling events
    bool rmbPressed = false;
    while(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        rmbPressed = true;
    }
    if(rmbPressed)
    {
        if(selectedUnit != nullptr)
        {
            std::pair<float, float> dest = std::make_pair(cursorPosition.x, cursorPosition.y);
            float scale = static_cast<float>(viewSize.x) / static_cast<float>(windowSize.x);
            dest.first = viewCenter.x + (dest.first - windowSize.x / 2) * scale;
            dest.second = viewCenter.y + (dest.second - windowSize.y / 2) * scale;
            std::cerr << "Commanded movement to: (" << dest.first << ", " << dest.second << ")" << std::endl;
            dest.first = std::max(dest.first, 0.0f);
            dest.second = std::max(dest.second, 0.0f);

            selectedUnit->move(dest);
        }
        rmbPressed = false;
    }
}

