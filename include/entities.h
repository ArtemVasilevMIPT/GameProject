#pragma once
#include "core.h"
#include <cmath>
#include <queue>
#include "pathfinding.h"
#include <chrono>

class Projectile : public Object
{
private:
    int count = 0;
    int lifeTime = 11;
public:
    Projectile();
    void set(float x0, float y0, float x, float y);
    ~Projectile() override;

    bool draw = false;
    void OnTick() override;
    void OnStart() override;
};


class Unit : public Entity {
private:
    int counter = 0;
    int projLifeTime = 5;
public:

    std::string name;

    int damage;
    float range;
    float rate_of_fire;
    Entity* target;
    std::chrono::time_point<std::chrono::steady_clock> time_last_shot;
    float speed = 1.0f;
    //Projectile currentProj;

    std::queue<std::pair<float, float>> currentPath;

    Unit() = default;
    ~Unit() = default;
    Unit(const Unit& other);

    Entity* clone() const override;

    void OnStart() override;
    void OnTick() override;
    void move(std::pair<float, float> destPoint) override;
    void shoot(Entity* ent) override;
    void setPosition(float x, float y);
    void destroy() override;
};


class Building : public Entity {
public:
    
    std::string name;


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
    HQ(const HQ& other);
    Entity* clone() const override;

    void destroy() override;
};


class Factory : public Building {
public:

    std::unordered_map<std::string, Unit> units;
    std::chrono::time_point<std::chrono::steady_clock> buildStart;
    std::string currentUnit = "";
    std::queue<std::string> buildQueue;
    std::pair<float, float> rallyPoint;

    Factory() = default;
    ~Factory() = default;
    Factory(const Factory& other);
    Entity* clone() const override;

    void OnStart() override;
    void OnTick() override;
    void build(const std::string& unit);
    void setRallyPoint(float x, float y);
};


//Builders

class RedUnitBuilder : Builder {
private:
    Unit* unit = nullptr;
public:
    void build() override;
    Unit* getResult();
};

class BlueUnitBuilder : Builder {
private:
    Unit* unit = nullptr;
public:
    void build() override;
    Unit* getResult();
};

class RedHQBuilder : Builder {
private:
    HQ* hq = nullptr;
public:
    void build() override;
    HQ* getResult();
};

class BlueHQBuilder : Builder {
private:
    HQ* hq = nullptr;
public:
    void build() override;
    HQ* getResult();
};

class RedFactoryBuilder : Builder {
private:
    Factory* factory = nullptr;
public:
    void build() override;
    Factory* getResult();
};

class BlueFactoryBuilder : Builder {
private:
    Factory* factory = nullptr;
public:
    void build() override;
    Factory* getResult();
};


