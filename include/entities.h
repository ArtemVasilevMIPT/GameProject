#pragma once
#include "core.h"
#include <cmath>
#include <queue>
#include "pathfinding.h"
#include <ctime>

class Unit : public Object {
public:

    std::string name;
    int hp;
    std::pair<float, float> coordinates;
    int damage;
    float range;
    float rate_of_fire;
    Object* target;
    size_t time_next_shot;
    float speed = 1.0f;
    std::string currentCommand = "STANDBY"; //Stores current command

    //List of commands:
    //* MOVE - unit is moving to its destination
    //* SHOOT - unit shoots given target
    //* STANDBY - unit does nothing

    std::queue<std::pair<float, float>> currentPath;

    Unit() = default;
    ~Unit() = default;

    void OnStart() override;
    void OnTick() override;
    void move(std::pair<float, float> destPoint);
    void shoot(Object* target);
    void setCommand(std::string& command);
    void destroy();    
};

class Building : public Object {
public:
    
    std::string name;
    int hp;

    Building() = default;
    ~Building() = default;

    void OnStart() override;
    void OnTick() override;
    virtual void destroy();
};

class HQ : public Building {
public: 
    HQ() = default;
    ~HQ() = default;

    void destroy() override;
};

class Factory : public Building {
public:

    std::unordered_map<std::string, Unit> units;
    std::queue<std::string> buildQueue;
    std::pair<float, float> rallyPoint;

    Factory() = default;
    ~Factory() = default;

    void OnStart() override;
    void OnTick() override;
    void build();
    void destroy() override;
};

class TestUnitBuilder : Builder
{
private:
    Unit* unit;
public:
    void build() override;
    void addNavigation(NavMesh& mesh);
    void reset() override;
    Unit* getResult();
};