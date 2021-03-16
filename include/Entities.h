#pragma once
#include "core.h"
#include <cmath>
#include <list>
#include <queue>

class Unit : public Object {
public:

    std::string name;
    int hp;
    std::pair<float, float> coordinaties;
    std::string currentCommant;
    std::list<std::pair<float, float>> currentPath;

    Unit() = default;
    ~Unit() = default;

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

    void build();
    void destroy() override;
};