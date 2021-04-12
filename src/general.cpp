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
    //Handling user input
    //Right Mouse Button
    bool rmbPressed = false;
    while(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        rmbPressed = true;
    }
    bool lmbPressed = false;
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        lmbPressed = true;
    }
    std::pair<float, float> dest = std::make_pair(cursorPosition.x, cursorPosition.y);
    if(lmbPressed || rmbPressed)
    {
        float scale = static_cast<float>(viewSize.x) / static_cast<float>(windowSize.x);
        dest.first = viewCenter.x + (dest.first - static_cast<float>(windowSize.x) / 2.0f) * scale;
        dest.second = viewCenter.y + (dest.second - static_cast<float>(windowSize.y) / 2.0f) * scale;
        dest.first = std::max(dest.first, 0.0f);
        dest.second = std::max(dest.second, 0.0f);
    }
    if(rmbPressed)
    {
        if(selectedUnit != nullptr)
        {
            //Checking for context actions
            //Looking for object
            Object* clickedObject = nullptr;
            for(auto& obj : Object::currentScene->getObjects())
            {
                SpriteComponent *comp = obj->GetComponent<SpriteComponent>();
                if (comp != nullptr && comp->enabled)
                {
                    sf::FloatRect boundingBox = comp->GetSprite().getGlobalBounds();
                    if (boundingBox.contains(cursorPosition.x, cursorPosition.y))
                    {
                        clickedObject = obj;
                        break;
                    }
                }
            }
            //
            if(dynamic_cast<Unit*>(selectedUnit) != nullptr)
            {
                if (clickedObject != nullptr)
                {
                    //Command to shoot
                    if (dynamic_cast<Unit *>(selectedUnit) != nullptr)
                    {
                        selectedUnit->shoot(dynamic_cast<Entity *>(clickedObject));
                    }
                } else
                {
                    //Command to move
                    selectedUnit->move(dest);
                }
            } else if(dynamic_cast<Factory*>(selectedUnit) != nullptr)
            {
                Factory* selected = dynamic_cast<Factory*>(selectedUnit);
                if(clickedObject == nullptr)
                {
                    selected->setRallyPoint(dest.first, dest.second);
                }
            }
            //
        }
        rmbPressed = false;
    }
    //Left Mouse Button

    if(lmbPressed)
    {
        //Selecting/Deselecting units
        //Looking for object
        Object* clickedObject = nullptr;
        for(auto& obj : Object::currentScene->getObjects())
        {
            SpriteComponent *comp = obj->GetComponent<SpriteComponent>();
            if (comp != nullptr && comp->enabled)
            {
                sf::FloatRect boundingBox = comp->GetSprite().getGlobalBounds();
                if (boundingBox.contains(cursorPosition.x, cursorPosition.y))
                {
                    clickedObject = obj;
                    break;
                }
            }
        }
        //
        if(selectedUnit != nullptr)
        {
            selectedUnit->selected = false;
        }
        if(clickedObject != nullptr)
        {
            selectedUnit = dynamic_cast<Entity*>(clickedObject);
        }
        else
        {
            selectedUnit = nullptr;
        }
        //
        lmbPressed = false;
    }

    //Will be moved to ui
    bool fPressed = false;
    while(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        fPressed = true;
    }
    if(fPressed)
    {
        auto* selected = dynamic_cast<Factory*>(selectedUnit);
        if(selected != nullptr)
        {
            if (selected->faction == "RED")
            {
                selected->build("RedUnit");
            } else
            {
                selected->build("BlueUnit");
            }
        }
    }
}

