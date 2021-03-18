#include <iostream>
#include "core.h"
#include "graphics.h"
#include "general.h"
#include "gui.h"
#include "entities.h"


int main()
{
    Scene sc;
    Object::currentScene = &sc;
    //For testing only
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");
    Player pl(window);

    Map levelMap;
    levelMap.load("../data/textures/map3.png");
    window.setSize(levelMap.getTexture().getSize());
    NavMesh mesh(window.getSize().x, window.getSize().y);

    //building unit
    TestUnitBuilder bld;
    bld.reset();
    bld.build();
    bld.addNavigation(mesh);
    Unit* testUnit = bld.getResult();
    //
    pl.selectedUnit = testUnit;

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
