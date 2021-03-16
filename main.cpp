#include <iostream>
#include "core.h"
#include "graphics.h"
#include "general.h"
#include "gui.h"

int main()
{
    //For testing only
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");
    Player pl(window);
    sf::Texture t;
    t.loadFromFile("../data/textures/avatar.jpg");
    sf::Sprite sp;
    sp.setTexture(t);
    sp.setPosition(400, 300);  
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
        pl.OnTick();
        window.clear();
        window.draw(sp);
        window.setView(pl.GetComponent<CameraComponent>()->GetCamera().GetView());
        window.display();
    }
    //
    return 0;
}
