#pragma once
#include "core.h"
#include <cmath>
#include <queue>
#include "pathfinding.h"
#include <ctime>

class Entity : public Object {
public:
    bool selected = false;
    std::string currentCommand = "STANDBY"; //Stores current command

    //List of commands:
    //* MOVE - unit is moving to its destination
    //* SHOOT - unit shoots given target
    //* STANDBY - unit does nothing

    Entity();
    ~Entity() override = default;

    Entity(const Entity& other);
    virtual Entity* clone() const;

    void OnStart() override;
    void OnTick() override;
    virtual void move(std::pair<float, float> destPoint);
    virtual void shoot(Entity* target);
    virtual void destroy();
    void setCommand(std::string& command);

};

class Unit : public Entity {
public:

    std::string name;
    int hp;
    std::pair<float, float> coordinates;
    int damage;
    float range;
    float rate_of_fire;
    Entity* target;
    size_t time_next_shot;
    float speed = 1.0f;

    std::queue<std::pair<float, float>> currentPath;

    Unit() = default;
    ~Unit() = default;
    Unit(const Unit& other);

    virtual Entity* clone() const;

    void OnStart() override;
    void OnTick() override;
    void move(std::pair<float, float> destPoint) override;
    void shoot(Entity* target) override;

    void destroy() override;
};

class Building : public Entity {
public:
    
    std::string name;
    int hp;

    Building() = default;
    Building(const Building& other);
    ~Building() override = default;

    Entity* clone() const override;

    void OnStart() override;
    void OnTick() override;
    void destroy() override;
};

class HQ : public Building {
public: 
    HQ() = default;
    ~HQ() = default;
    HQ(const HQ* other);
    Entity* clone() const override;

    void destroy() override;
};

class Factory : public Building {
public:

    std::unordered_map<std::string, Unit> units;
    std::queue<std::string> buildQueue;
    std::pair<float, float> rallyPoint;

    Factory() = default;
    ~Factory() = default;
    Factory(const Factory& other);
    Entity* clone() const override;

    void OnStart() override;
    void OnTick() override;
    void build();
    void destroy() override;
};

class TestUnitBuilder : Builder
{
private:
    Unit* unit = nullptr;
public:
    void build() override;
    void addNavigation(NavMesh& mesh);
    void reset() override;
    Unit* getResult();
};