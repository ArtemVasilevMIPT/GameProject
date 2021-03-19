#pragma once
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <list>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Object;

class Scene
{
private:
    std::list<Object*> objects;
public:
    Scene() = default;
    Scene(std::string path);
    ~Scene();

    void load(std::string path);
    void addObject(Object* obj);
    void removeObject(std::list<Object*>::iterator& iter);
    const std::list<Object*>& getObjects()
    {
        return objects;
    }
};

class Component
{
public :
    std::string name = "Component";

    Component();

    virtual ~Component();
};

class Object
{

private:
    std::unordered_map<std::string,Component*> components; //Storage of all object's components

public:
    Object();
    Object(const Object& obj) = delete;
    virtual ~Object();

    static Scene* currentScene;
    std::list<Object*>::iterator _objPos; //Position in scene's object storage

    virtual void OnStart() = 0; //Called when game starts
    virtual void OnTick() = 0; //Called every tick
    virtual void OnClick(); //Called when clicked
    virtual void OnHover(); //Called when mouse hovers over the object

    //Method that adds specific component to the base class
    template<typename T>
    void AddComponent(T component)
    {
        auto it = components.find(component.name);
        if(it == components.end())
        {
            T* newComponent = new T(component);

            components.insert({component.name, dynamic_cast<Component*>(newComponent)});
        }
    }

    //Method that returns a pointer to the specific component of the base class
    template <typename T>
    T* GetComponent()
    {
        std::string name = typeid(T).name();
        //Removing digits from the beginning
            int i = 0;
            while(isdigit(name[i]))
            {
                ++i;
            }
            name = name.substr(i, name.size() - i);
        //
        auto it = components.find(name);
        if(it == components.end())
        {
            return nullptr;
        }

        T* component = dynamic_cast<T*>(it->second);
        return component;
    }
};

class Map
{
private:
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
public:
    Map() = default;
    void load(std::string texturePath);
    sf::Sprite getSprite();

    sf::Texture& getTexture()
    {
        return mapTexture;
    }
};

class Builder
{
public:
    virtual void build() = 0;
    virtual void reset() = 0;
};

class PrototypeFactory {
private:
    std::unordered_map<std::string, Object*> prototypes;
public:
    PrototypeFactory();
    ~PrototypeFactory();

    Object* clone(std::string name);
};