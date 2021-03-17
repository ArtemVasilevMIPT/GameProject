#include <iostream>
#include "core.h"
#include "graphics.h"
#include "general.h"
#include "gui.h"

class TestObject : public Object
{
public:
    void OnTick() override {}
    void OnStart() override {}
};

int main()
{
    Scene sc;
    Object::currentScene = &sc;
    //For testing only
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");
    Player pl(window);
    TestObject to;
    to.AddComponent(SpriteComponent("../data/textures/avatar.jpg"));
    //to.GetComponent<SpriteComponent>()->SetPosition(400.0, 300.0);
    Map levelMap;
    levelMap.load("../data/textures/map3.png");
    window.setSize(levelMap.getTexture().getSize());
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
        //Actions loop
        for(auto& elem : sc.getObjects())
        {
            elem->OnTick();
        }
        //
        //Graphics pipeline
        window.clear();
        window.draw(levelMap.getSprite());
        for(auto& elem : sc.getObjects())
        {
            SpriteComponent* comp = elem->GetComponent<SpriteComponent>();
            if(comp != nullptr)
            {
                window.draw(comp->GetSprite());
            }
        }
        window.setView(pl.GetComponent<CameraComponent>()->GetCamera().GetView());
        window.display();
    }
    //
    return 0;
}
