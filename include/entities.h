#pragma once
#include "core.h"
#include <cmath>
#include <list>
#include <queue>

class Unit : public Object {
public:

    std::string name;
    int hp;
    std::pair<float, float> coordinates;
    std::string currentCommand;
    std::list<std::pair<float, float>> currentPath;

    Unit() = default;
    ~Unit() = default;

    void OnStart() override;
    void OnTick() override;
    void move(std::pair<float, float> destPoint);
    void shoot(std::pair<float, float> destPoint);
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
    void reset() override;
    Unit* getResult()
    {
        return unit;
    }
};