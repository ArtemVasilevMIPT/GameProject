//
// Created by marcille on 06.03.2021.
//
#include <fstream>
#include "core.h"
#include "pathfinding.h"
#include "graphics.h"
#include "gui.h"
#include "entities.h"
#include "general.h"

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
    currentScene->addObject(this);
}

void Object::destroyObject(Object *obj)
{
    delete obj;
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

Scene::Scene(const std::string& path)
{

}

void Scene::save(const std::string &path)
{
    std::ofstream output(path);
    boost::archive::text_oarchive oa{output};
    oa.register_type<Entity>();
    oa.register_type<SpriteComponent>();
    oa.register_type<CameraComponent>();
    oa.register_type<NavComponent>();
    oa.register_type<Unit>();
    oa.register_type<Building>();
    oa.register_type<Factory>();
    oa.register_type<HQ>();
    oa.register_type<Player>();
    oa << *this;
    output.close();
}

void Scene::load(const std::string& path)
{
    std::ifstream input(path);
    boost::archive::text_iarchive ia{input};
    ia.register_type<Entity>();
    ia.register_type<SpriteComponent>();
    ia.register_type<CameraComponent>();
    ia.register_type<NavComponent>();
    ia.register_type<Unit>();
    ia.register_type<Building>();
    ia.register_type<Factory>();
    ia.register_type<HQ>();
    ia.register_type<Player>();
    ia >> *this;
    input.close();
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

Scene::Scene()
{
    Object::currentScene = this;
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

NavMesh::NavMesh(size_t ox, size_t oy) {
    navMap.resize(ox);
    for(size_t i= 0; i < ox; ++i) {
        navMap[i].resize(oy);
    }
}
const std::vector<bool>& NavMesh::operator[](size_t x) const {
    return navMap[x];
}
void NavMesh::placeObstacle(std::pair<size_t, size_t> position, size_t size_x, size_t size_y) {
    for(size_t i = position.first; i < position.first + size_x; ++i) {
        for(size_t j = position.second; j < position.second + size_y; ++j) {
            navMap[i][j] = true;
        }
    }
}

void NavMesh::removeObstacle(std::pair<size_t, size_t> position, size_t size_x, size_t size_y) {
    for(size_t i = position.first; i < position.first + size_x; ++i) {
        for(size_t j = position.second; j < position.second + size_y; ++j) {
            navMap[i][j] = true;
        }
    }
}

void NavMesh::setSize(size_t x, size_t y)
{
    navMap.resize(x);
    for(auto& elem : navMap)
    {
        elem.resize(y);
    }
}

//Entity

Entity::Entity()
{}

Entity::Entity(const Entity& other) : Object(other),
                                      selected(other.selected), hp(other.hp), coordinates(other.coordinates), currentCommand(other.currentCommand) {};

Entity* Entity::clone() const {
    return new Entity(*this);
}

void Entity::OnStart()
{}

void Entity::OnTick()
{}

void Entity::shoot(Entity *target)
{}

void Entity::move(std::pair<float, float> destPoint)
{}

void Entity::setCommand(enum Command command)
{
    currentCommand = command;
}

void Entity::destroy()
{}

//PrototypeFactory

PrototypeFactory::PrototypeFactory() {
    RedUnitBuilder redUnitBuilder;
    prototypes["RedUnit"] = redUnitBuilder.getResult();
    BlueUnitBuilder blueUnitBuilder;
    prototypes["BlueUnit"] = blueUnitBuilder.getResult();

    RedHQBuilder redHQBuilder;
    prototypes["RedHQ"] = redHQBuilder.getResult();
    BlueHQBuilder blueHQBuilder;
    prototypes["BlueHQ"] = blueHQBuilder.getResult();

    RedFactoryBuilder redFactoryBuilder;
    prototypes["RedFactory"] = redFactoryBuilder.getResult();
    BlueFactoryBuilder blueFactoryBuilder;
    prototypes["BlueFactory"] = blueFactoryBuilder.getResult();
    for(auto& elem : prototypes)
    {
        auto* comp = elem.second->GetComponent<SpriteComponent>();
        if(comp != nullptr)
            comp->enabled = false;
    }
}

PrototypeFactory::~PrototypeFactory() {
    for(auto& elem : prototypes)
    {
        delete elem.second;
    }
}

Entity* PrototypeFactory::clone(std::string name) {
    return prototypes[name]->clone();
}