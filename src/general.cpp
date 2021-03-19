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
        std::cerr << "Clicked on " << dest.first << " " << dest.second <<  std::endl;
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
                if (comp != nullptr)
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
            if(clickedObject != nullptr)
            {
                //Command to shoot

            }
            else
            {
                //Command to move
                std::cerr << "Commanded movement to: (" << dest.first << ", " << dest.second << ")" << std::endl;
                selectedUnit->move(dest);
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
            if (comp != nullptr)
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
            std::cerr << "Deselected!" << std::endl;
        }
        if(clickedObject != nullptr)
        {
            selectedUnit = dynamic_cast<Entity*>(clickedObject);
            std::cerr << "Selected! " << (selectedUnit != nullptr)<< std::endl;
        }
        else
        {
            selectedUnit = nullptr;
        }
        //
        lmbPressed = false;
    }
    /*
    //E key
    bool ePressed = false;
    while(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        ePressed = true;
    }
    if(ePressed)
    {
        this->GetComponent<CameraComponent>()->zoomCamera(1.6f);
        if(window->getView().getSize().x > windowSize.x)
        {
            sf::View v;
            v.setSize(windowSize.x, windowSize.y);
            v.setCenter(viewCenter);
            this->GetComponent<CameraComponent>()->GetCamera().SetView(v);
        }
        ePressed = false;
    }
    //Q key
    bool qPressed = false;
    while(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        qPressed = true;
    }
    if(qPressed)
    {
        this->GetComponent<CameraComponent>()->zoomCamera(0.0625f);
        if(window->getView().getSize().x < 100)
        {
            sf::View v;
            v.setSize(viewSize.x, viewSize.y);
            v.setCenter(viewCenter);
            this->GetComponent<CameraComponent>()->GetCamera().SetView(v);
        }
        qPressed = false;
    }
    */
}

