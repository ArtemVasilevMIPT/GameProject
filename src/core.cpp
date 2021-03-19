//
// Created by marcille on 06.03.2021.
//

#include "core.h"
#include "pathfinding.h"
#include "graphics.h"
#include "gui.h"

Scene* Object::currentScene;

Object::~Object()
{
    currentScene->removeObject(_objPos);
    for(auto& component : components)
    {
        delete component.second;
    }

}

Object::Object()
{
    currentScene->addObject(this);
}

void Object::OnClick() {}
void Object::OnHover() {}

Object::Object(const Object &obj)
{
    for(auto& elem : obj.components)
    {
        std::string compName = elem.first;
        if(compName == "SpriteComponent")
        {
            auto* newComp = new SpriteComponent(*(dynamic_cast<SpriteComponent*>(elem.second)));
            this->AddComponent(*newComp);
        }
        else if(compName == "NavComponent")
        {
            auto* newComp = new NavComponent(*(dynamic_cast<NavComponent*>(elem.second)));
            this->AddComponent(*newComp);
        }
        else if(compName == "CameraComponent")
        {
            auto* newComp = new CameraComponent(*(dynamic_cast<CameraComponent*>(elem.second)));
            this->AddComponent(*newComp);
        }
        else if(compName == "UIComponent")
        {
            auto* newComp = new UIComponent(*(dynamic_cast<UIComponent*>(elem.second)));
            this->AddComponent(*newComp);
        }
    }
}

Component::Component() = default;
Component::~Component() = default;

Scene::~Scene()
{
    while(!objects.empty())
    {
        delete *objects.begin();
    }
}

Scene::Scene(std::string path)
{

}

void Scene::load(std::string path)
{

}

void Scene::addObject(Object *obj)
{
    objects.push_back(obj);
    auto it = objects.end();
    --it;
    obj->_objPos = it;
}

void Scene::removeObject(std::list<Object *>::iterator &iter)
{
    objects.erase(iter);
}

void Map::load(std::string texturePath)
{
    mapTexture.loadFromFile(texturePath);
    mapSprite.setTexture(mapTexture);
}

sf::Sprite Map::getSprite()
{
    sf::Sprite sp;
    sp.setTexture(mapTexture);
    return mapSprite;
}
