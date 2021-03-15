//
// Created by marcille on 06.03.2021.
//

#include "core.h"

Object::~Object()
{

    for(auto& component : components)
    {
        delete component.second;
    }

}

Object::Object() {}
void Object::OnClick() {}
void Object::OnHover() {}

Object::Object(const Object &obj)
{
    for(auto& component : this->components)
    {
        delete[] component.second;
    }

    this->components = obj.components;
}

Component::Component() = default;
Component::~Component() = default;

Scene::Scene(std::string path)
{

}

void Scene::load(std::string path)
{

}

void Scene::addObject(Object *obj)
{
    objects.push_back(obj);
    obj->_objPos = objects.end()--;
}

void Scene::removeObject(std::list<Object*>::iterator pos)
{
    objects.erase(pos);
}
