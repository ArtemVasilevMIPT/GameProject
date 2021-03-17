#include "entities.h"
#include "graphics.h"
#include "gui.h"

void Unit::move(std::pair<float, float> destPoint) {

}

void Unit::shoot(std::pair<float, float> destPoint) {

}

void Unit::destroy() {

}

void Unit::OnTick()
{

}

void Unit::OnStart()
{

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
    unit = new Unit;
    unit->AddComponent(SpriteComponent("../data/textures/units/redUnit1.png"));
}


void TestUnitBuilder::reset()
{

}
