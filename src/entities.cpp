#include "entities.h"
#include "graphics.h"
#include "gui.h"
#include <iostream>

Entity::Entity(const Entity* other) : Object(other), 
    selected(other->selected), currentCommand(other->currentCommand) {};

Object* Entity::clone() const {
    return new Entity(this);
}

void Entity::setCommand(std::string& command) {

}

Unit::Unit(const Unit* other) : Entity(other), name(other->name), hp(other->hp),
    coordinates(other->coordinates), damage(other->damage), range(other->range), rate_of_fire(other->rate_of_fire),
    target(nullptr), time_next_shot(time(NULL) + rate_of_fire), speed(other->speed) {};

Object* Unit::clone() const {
    return new Unit(this);
}


void Unit::move(std::pair<float, float> destPoint)
{
    currentCommand = "MOVE";
    currentPath = this->GetComponent<NavComponent>()->findPath(coordinates, destPoint, speed);
    std::cerr << "Moving to coordinates: (" << destPoint.first << ", " << destPoint.second << ")" << std::endl;
}

void Unit::shoot(Entity* target) {

}

void Unit::destroy() {

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
            this->GetComponent<SpriteComponent>()->SetPosition(newPos.first, newPos.second);
            coordinates.first = newPos.first;
            coordinates.second = newPos.second;
            currentPath.pop();
        }
    }
    else if(currentCommand == "SHOOT")
    {

    }
    else
    {

    }
}

void Unit::OnStart()
{

}

Building::Building(const Building* other) : Entity(other),
    name(other->name), hp(other->hp) {};

Object* Building::clone() const {
    return new Building(this);
}

void Building::destroy() {

}

void Building::OnStart()
{

}

void Building::OnTick()
{

}

HQ::HQ(const HQ* other) : Building(other) {};

Object* HQ::clone() const {
    return new HQ(this);
}

void HQ::destroy() {
    
}

Factory::Factory(const Factory* other) : Building(other), 
    units(other->units), buildQueue(other->buildQueue), rallyPoint(other->rallyPoint) {};

Object* Factory::clone() const {
    return new Factory(this);
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

void TestUnitBuilder::build()
{
    unit->AddComponent(SpriteComponent("../data/textures/units/redUnit1.png"));
    unit->name = "Test";
    //Optional
    unit->coordinates.second = 40;
    unit->coordinates.first = 40;
    //
    unit->currentCommand = "STANDBY";
    unit->hp = 50;
    unit->speed = 3.0f;
}


void TestUnitBuilder::reset()
{
    unit = new Unit;
}

void TestUnitBuilder::addNavigation(NavMesh& mesh)
{
    unit->AddComponent(NavComponent(mesh));
}

Unit *TestUnitBuilder::getResult()
{
    return unit;
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
