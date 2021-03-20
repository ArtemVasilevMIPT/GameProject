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

class Entity : public Object {
public:
    bool selected = false;
    std::string faction;
    std::pair<float, float> coordinates;
    int hp;
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
    virtual void shoot(Entity* ent);
    virtual void destroy();

    void setCommand(std::string& command);

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


//PrototypeFactory

class PrototypeFactory {
private:
    std::unordered_map<std::string, Entity*> prototypes;
public:
    PrototypeFactory();
    ~PrototypeFactory();

    Entity* clone(std::string name);
};