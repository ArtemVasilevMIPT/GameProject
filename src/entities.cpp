#include "entities.h"
#include "graphics.h"
#include "gui.h"
#include <iostream>


//Unit

Unit::Unit(const Unit& other) : Entity(other), name(other.name),
     damage(other.damage), range(other.range), rate_of_fire(other.rate_of_fire),
    target(nullptr), time_last_shot(std::chrono::steady_clock::now()), speed(other.speed) {};

Entity* Unit::clone() const {
    auto* unit = new Unit(*this);
    unit->GetComponent<SpriteComponent>()->enabled = true;
    return unit;
}


void Unit::move(std::pair<float, float> destPoint)
{
    currentCommand = "MOVE";
    currentPath = this->GetComponent<NavComponent>()->findPath(coordinates, destPoint, speed);
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
        }
        else
        {
            std::pair<float, float> newPos = currentPath.front();
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

void Unit::setPosition(float x, float y)
{
    coordinates.first = x;
    coordinates.second = x;
    this->GetComponent<SpriteComponent>()->SetPosition(x, y);
}


//Building

Building::Building(const Building& other) : Entity(other),
    name(other.name){};

Entity* Building::clone() const {
    auto* building = new Building(*this);
    building->GetComponent<SpriteComponent>()->enabled = true;
    return building;
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
    auto* hq = new HQ(*this);
    hq->GetComponent<SpriteComponent>()->enabled = true;
    return hq;
}

void HQ::destroy() {
    
}


//Factory

Factory::Factory(const Factory& other) : Building(other), 
    units(other.units), buildQueue(other.buildQueue), rallyPoint(other.rallyPoint) {};

Entity* Factory::clone() const {
    auto* factory = new Factory(*this);
    factory->GetComponent<SpriteComponent>()->enabled = true;
    return factory;
}

void Factory::build(std::string unit)
{
    buildQueue.push(unit);
    currentCommand = "BUILD";
}
void Factory::destroy() {

}

void Factory::OnStart()
{
}

void Factory::OnTick()
{
    if(currentCommand == "BUILD")
    {
        if(currentUnit.empty())
        {
            buildStart = std::chrono::steady_clock::now();
            currentUnit = buildQueue.front();
        }
        else
        {
            auto currTime = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(currTime - buildStart).count();
            //Build time == 10 sec
            if(duration >= 3)
            {
                Unit* unit = dynamic_cast<Unit*>(Object::currentScene->prFactory->clone(currentUnit));
                unit->setPosition(coordinates.first - 30, coordinates.second - 30);
                unit->move(rallyPoint);
                buildQueue.pop();
                if(buildQueue.empty())
                {
                    currentCommand = "STANDBY";
                    currentUnit = "";
                }
                else
                {
                    currentUnit = buildQueue.front();
                    buildStart = std::chrono::steady_clock::now();
                }
            }
        }
    }
}

void Factory::setRallyPoint(float x, float y)
{
    rallyPoint.first = x;
    rallyPoint.second = y;
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
    unit->name = "BlueUnit";
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

void RedFactoryBuilder::build()
{
    factory->AddComponent(SpriteComponent("../data/textures/buildings/redFactory.png"));
    factory->name = "RedFactory";
    auto* comp = factory->GetComponent<SpriteComponent>();
    factory->rallyPoint = std::make_pair(comp->GetPosition().first + comp->GetSize().first,
                                         comp->GetPosition().second + comp->GetSize().second);
    factory->hp = 100;
    factory->faction = "RED";
}


Factory* RedFactoryBuilder::getResult() {
    factory = new Factory;
    build();
    return factory;
}

void BlueFactoryBuilder::build() {
    factory->AddComponent(SpriteComponent("../data/textures/buildings/blueFactory.png"));
    factory->name = "BlueFactory";
    auto* comp = factory->GetComponent<SpriteComponent>();
    factory->rallyPoint = std::make_pair(comp->GetPosition().first + comp->GetSize().first,
                                         comp->GetPosition().second + comp->GetSize().second);
    factory->hp = 100;
    factory->faction = "BLUE";
}


Factory* BlueFactoryBuilder::getResult() {
    factory = new Factory;
    build();
    return factory;
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
