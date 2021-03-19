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
    Map levelMap;
    levelMap.load("../data/textures/map3.png");
    //window.setSize(levelMap.getTexture().getSize());
    sf::RenderWindow window(sf::VideoMode(levelMap.getTexture().getSize().x, levelMap.getTexture().getSize().y), "My Window");
    Player pl(window);


    NavMesh mesh(window.getSize().x, window.getSize().y);

    //building unit
    TestUnitBuilder bld;
    bld.reset();
    bld.build();
    bld.addNavigation(mesh);
    Unit* testUnit = bld.getResult();

    bld.reset();
    bld.build();
    bld.addNavigation(mesh);
    Unit* testUnit2 = bld.getResult();
    testUnit2->faction = "BLUE";
    testUnit2->coordinates = std::make_pair(400.f, 400.f);
    testUnit2->GetComponent<SpriteComponent>()->SetPosition(400.f, 400.f);
    //
    pl.selectedUnit = testUnit;

    window.setView(window.getDefaultView());
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
        window.setView(pl.GetComponent<CameraComponent>()->GetCamera().GetView());
        window.draw(levelMap.getSprite());
        for(auto& elem : sc.getObjects())
        {
            SpriteComponent* comp = elem->GetComponent<SpriteComponent>();
            if(comp != nullptr)
            {
                window.draw(comp->GetSprite());
            }
        }
        window.display();
    }
    //
    return 0;
}
