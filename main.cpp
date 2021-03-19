#include <iostream>
#include <thread>
#include <chrono>
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
    sc.currMap.load("../data/textures/map3.png");
    sf::RenderWindow window(sf::VideoMode(sc.currMap.getTexture().getSize().x, sc.currMap.getTexture().getSize().y), "My Window");
    Player pl(window);
    sc.currMap.mesh.setSize(window.getSize().x, window.getSize().y);

    //building unit
    TestUnitBuilder bld;
    bld.reset();
    bld.build();
    Unit* testUnit = bld.getResult();

    bld.reset();
    bld.build();
    Unit* testUnit2 = bld.getResult();
    testUnit2->faction = "BLUE";
    testUnit2->coordinates = std::make_pair(400.f, 400.f);
    testUnit2->GetComponent<SpriteComponent>()->SetPosition(400.f, 400.f);
    //
    pl.selectedUnit = testUnit;

    window.setView(window.getDefaultView());
    //FPS lock
    auto lastIteration = std::chrono::steady_clock::now();
    //
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
        window.draw(sc.currMap.getSprite());
        for(auto& elem : sc.getObjects())
        {
            SpriteComponent* comp = elem->GetComponent<SpriteComponent>();
            if(comp != nullptr)
            {
                window.draw(comp->GetSprite());
            }
        }
        window.display();
        //FPS lock
        auto currTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - lastIteration);
        if(duration.count() < 1000 / 60)//60 FPS
        {
            std::this_thread::sleep_for(duration);
        }
        //
    }
    //
    return 0;
}
