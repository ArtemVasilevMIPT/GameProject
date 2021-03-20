#include "entities.h"
#include "graphics.h"
#include "gui.h"
#include <iostream>


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

void Entity::setCommand(std::string &command)
{
    currentCommand = command;
}

void Entity::destroy()
{}


//Unit

Unit::Unit(const Unit& other) : Entity(other), name(other.name),
     damage(other.damage), range(other.range), rate_of_fire(other.rate_of_fire),
    target(nullptr), time_last_shot(std::chrono::steady_clock::now()), speed(other.speed) {};

Entity* Unit::clone() const {
    return new Unit(*this);
}


void Unit::move(std::pair<float, float> destPoint)
{
    currentCommand = "MOVE";
    currentPath = this->GetComponent<NavComponent>()->findPath(coordinates, destPoint, speed);
    std::cerr << "Moving to coordinates: (" << destPoint.first << ", " << destPoint.second << ")" << std::endl;
}

void Unit::shoot(Entity* ent)
{
    if(ent->faction != faction)
    {
        currentCommand = "SHOOT";
        target = ent;
    }
}

void Unit::destroy()
{
    this->~Unit();
}

void Unit::OnTick()
{
    if(currentCommand == "MOVE")
    {
        if(currentPath.empty())
        {
            currentCommand = "STANDBY";
            std::cerr << "Stopped on coordinates: (" << coordinates.first << ", " << coordinates.second << ")\n";
        }
        else
        {
            std::pair<float, float> newPos = currentPath.front();
            //std::cerr << newPos.first << " " << newPos.second << std::endl;
            auto* comp = this->GetComponent<SpriteComponent>();
            comp->SetPosition(newPos.first, newPos.second);//Moving
            float len = sqrt((newPos.first - coordinates.first) * (newPos.first - coordinates.first) +
                            (newPos.second - coordinates.second) * (newPos.second - coordinates.second));
            float angle = asinf((newPos.second - coordinates.second) / len);
            if(newPos.first < coordinates.first)
            {
                angle = 180.f - angle;
            }
            comp->SetRotation(-angle);
            coordinates.first = newPos.first;
            coordinates.second = newPos.second;
            currentPath.pop();
        }
    }
    else if(currentCommand == "SHOOT")
    {
        sf::Vector2u size = this->GetComponent<SpriteComponent>()->GetSprite().getTexture()->getSize();
        std::pair<float, float> pos = std::make_pair(coordinates.first + size.x / 2,
                                                     coordinates.second + size.y / 2);
        sf::Vector2u targetSize = target->GetComponent<SpriteComponent>()->GetSprite().getTexture()->getSize();
        std::pair<float, float> targetPos = std::make_pair(target->coordinates.first + targetSize.x / 2,
                                                           target->coordinates.second + targetSize.y / 2);
        float distance = sqrt((pos.first - targetPos.first) * (pos.first - targetPos.first) +
                             (pos.second - targetPos.second) * (pos.second - targetPos.second));
        if(distance <= range)
        {
            auto currTime = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(currTime - time_last_shot).count();
            if(duration >= rate_of_fire)
            {
                time_last_shot = currTime;
                target->hp -= damage;
                std::cerr << "Shooting at target" << std::endl;
                //currentProj.set(pos.first, pos.second, targetPos.first, targetPos.second);
                if(target->hp <= 0)
                {
                    Object::destroyObject(target);
                    currentCommand = "STANDBY";
                }
            }
        }
        else
        {
            currentCommand = "STANDBY";
        }
    }
    else
    {

    }
}

void Unit::OnStart()
{

}


//Building

Building::Building(const Building& other) : Entity(other),
    name(other.name){};

Entity* Building::clone() const {
    return new Building(*this);
}

void Building::destroy() {

}

void Building::OnStart()
{

}

void Building::OnTick()
{

}


//HQ

HQ::HQ(const HQ& other) : Building(other) {};

Entity* HQ::clone() const {
    return new HQ(*this);
}

void HQ::destroy() {
    
}


//Factory

Factory::Factory(const Factory& other) : Building(other), 
    units(other.units), buildQueue(other.buildQueue), rallyPoint(other.rallyPoint) {};

Entity* Factory::clone() const {
    return new Factory(*this);
}

void Factory::build() {

}
void Factory::destroy() {

}

void Factory::OnStart()
{
}

void Factory::OnTick()
{
}


//Builders

void RedUnitBuilder::build() {
    unit->AddComponent(SpriteComponent("../data/textures/units/redTank.png"));
    unit->AddComponent(NavComponent(Object::currentScene->currMap.mesh));
    unit->name = "RedUnit";
    unit->faction = "RED";
    //Optional
    unit->coordinates.second = 40;
    unit->coordinates.first = 40;
    //
    unit->currentCommand = "STANDBY";
    unit->hp = 50;
    unit->speed = 1.f;
    unit->rate_of_fire = 1.0f;
    unit->range = 500.f;
    unit->damage = 10.f;
}


Unit* RedUnitBuilder::getResult() {
    unit = new Unit;
    build();
    return unit;
}

void BlueUnitBuilder::build() {
    unit->AddComponent(SpriteComponent("../data/textures/units/blueTank.png"));
    unit->AddComponent(NavComponent(Object::currentScene->currMap.mesh));
    unit->name = "RedUnit";
    unit->faction = "BLUE";
    //Optional
    unit->coordinates.second = 40;
    unit->coordinates.first = 40;
    //
    unit->currentCommand = "STANDBY";
    unit->hp = 50;
    unit->speed = 1.f;
    unit->rate_of_fire = 1.0f;
    unit->range = 500.f;
    unit->damage = 10.f;
}


Unit* BlueUnitBuilder::getResult() {
    unit = new Unit;
    build();
    return unit;
} 

void RedHQBuilder::build() {
    
}


HQ* RedHQBuilder::getResult() {
    hq = new HQ;
    build();
    return hq;
}

void BlueHQBuilder::build() {
    
}


HQ* BlueHQBuilder::getResult() {
    hq = new HQ;
    build();
    return hq;
}

void RedFactoryBuilder::build() {
    
}


Factory* RedFactoryBuilder::getResult() {
    factory = new Factory;
    build();
    return factory;
}

void BlueFactoryBuilder::build() {
    
}


Factory* BlueFactoryBuilder::getResult() {
    factory = new Factory;
    build();
    return factory;
}

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
}

PrototypeFactory::~PrototypeFactory() {
    delete prototypes["RedUnit"];
    delete prototypes["BlueUnit"];
    delete prototypes["RedHQ"];
    delete prototypes["BlueHQ"];
    delete prototypes["RedFactory"];
    delete prototypes["BlueFactory"];
}

Entity* PrototypeFactory::clone(std::string name) {
    return prototypes[name]->clone();
}

Projectile::Projectile()
{
    draw = false;
    this->AddComponent(SpriteComponent("../data/textures/laser.png"));
    this->GetComponent<SpriteComponent>()->enabled = false;
}

void Projectile::OnTick()
{
    if(count < lifeTime)
    {
        ++count;
    }
    else
    {
        if(draw)
        {
            std::cerr << "Disabled drawing" << std::endl;
            this->GetComponent<SpriteComponent>()->enabled = false;
            draw = false;
        }
    }
}

void Projectile::OnStart()
{
}

Projectile::~Projectile()
{}

void Projectile::set(float x0, float y0, float x, float y)
{
    float len = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
    float angle = asin((y - y0) / len);
    auto* comp = this->GetComponent<SpriteComponent>();
    comp->SetSize(len, 3);
    comp->SetPosition(x0, y0);
    comp->SetRotation(angle);
    comp->enabled = true;
    draw = true;
    count = 0;
}
