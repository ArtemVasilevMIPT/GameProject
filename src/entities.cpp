#include "entities.h"
#include "graphics.h"
#include "gui.h"


void Unit::move(std::pair<float, float> destPoint)
{
    currentCommand = "MOVE";
    currentPath = this->GetComponent<NavComponent>()->findPath(coordinates, destPoint, speed);
    std::cerr << "Moving to coordinates: (" << destPoint.first << ", " << destPoint.second << ")" << std::endl;
}

void Unit::shoot(std::pair<float, float> destPoint) {

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

void Unit::setCommand(std::string& command) {
    currentCommand = command;
}


void Building::destroy() {

}

void Building::OnStart()
{

}

void Building::OnTick()
{

}

void HQ::destroy() {
    
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
