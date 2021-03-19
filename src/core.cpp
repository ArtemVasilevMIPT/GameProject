//
// Created by marcille on 06.03.2021.
//

#include "core.h"
#include "entities.h"

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

PrototypeFactory::PrototypeFactory() {
    prototypes["unit1"] = new Unit();
    prototypes["HQ"] = new HQ();
    prototypes["Factory"] = new Factory();
}

PrototypeFactory::~PrototypeFactory() {
    delete prototypes["unit1"];
    delete prototypes["HQ"];
    delete prototypes["Factory"];
}

Object* PrototypeFactory::clone(std::string name) {
    return prototypes[name]->clone();
}