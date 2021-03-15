#include <iostream>
#include "core.h"
#include "graphics.h"
#include "general.h"
#include "gui.h"


class TestObject : public Object
{
public:
    void OnStart() override
    {}
    void OnTick() override
    {}
};


int main()
{
    //For testing only
    TestObject obj;
    obj.AddComponent(SpriteComponent("../data/textures/avatar.jpg"));
    sf::Sprite sp = obj.GetComponent<SpriteComponent>()->GetSprite();
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");
    obj.AddComponent(CameraComponent(window));

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();

            }
        }
        window.clear();
        //window.draw(sp);
        window.setView(obj.GetComponent<CameraComponent>()->GetCamera().GetView());
        window.display();
    }
    //
    return 0;
}
