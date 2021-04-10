#pragma once
#include <string>
#include <unordered_map>
#include <typeinfo>
#include <list>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>

class Object;
class Entity;
//PrototypeFactory

class PrototypeFactory {
private:
    std::unordered_map<std::string, Entity*> prototypes;
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        {
            ar & prototypes;
        }
    }
    //
public:
    PrototypeFactory();
    ~PrototypeFactory();
    Entity* clone(std::string name);
};

class NavMesh {
    std::vector<std::vector<bool>> navMap;
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & navMap;
    }
    //
public:

    NavMesh(size_t ox, size_t oy);
    NavMesh() = default;
    ~NavMesh() = default;

    const std::vector<bool>& operator[](size_t x) const;

    void setSize(size_t x, size_t y);
    void placeObstacle(std::pair<size_t, size_t> position, size_t size_x, size_t size_y);
    void removeObstacle(std::pair<size_t, size_t> position, size_t size_x, size_t size_y);
};

class Map
{
private:
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        //TODO implement
    }
    //
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
public:
    Map() = default;
    void load(std::string texturePath);
    sf::Sprite getSprite();
    NavMesh mesh;
    sf::Texture& getTexture()
    {
        return mapTexture;
    }
};

class Scene
{
private:
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & objects;
    }
    //
    std::list<Object*> objects;
public:
    Scene();
    explicit Scene(const std::string& path);
    ~Scene();

    //Serialization stuff
    void load(const std::string& path);
    void save(const std::string& path);
    //
    Map currMap;
    sf::RenderWindow* window = nullptr;
    PrototypeFactory* prFactory = nullptr;
    void addObject(Object* obj);
    void removeObject(std::list<Object*>::iterator& iter);
    const std::list<Object*>& getObjects()
    {
        return objects;
    }
};

class Component
{
private:
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & name;
        ar & enabled;
    }
    //
public :
    std::string name = "Component";
    bool enabled = true;//Enables/Disables component
    Component();

    virtual ~Component();
};

class Object
{

private:
    std::unordered_map<std::string,Component*> components; //Storage of all object's components
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & components;
    }
    //
public:
    Object();
    Object(const Object& obj);
    virtual ~Object();

    static Scene* currentScene;
    std::list<Object*>::iterator _objPos; //Position in scene's object storage

    virtual void OnStart() = 0; //Called when game starts
    virtual void OnTick() = 0; //Called every tick
    virtual void OnClick(); //Called when clicked
    virtual void OnHover(); //Called when mouse hovers over the object
    static void destroyObject(Object* obj); //Destroys given object
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



class Builder {
public:
    virtual void build() = 0;
};

enum Command {STANDBY, MOVE, SHOOT, BUILD, SET_RALLY_POINT};

class Entity : public Object {
private:
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Object>(*this);
        ar & selected;
        ar & faction;
        ar & coordinates;
        ar & hp;
        ar & currentCommand;
    }
    //
public:
    bool selected = false;
    std::string faction;
    std::pair<float, float> coordinates;
    int hp;
    enum Command currentCommand = STANDBY; //Stores current command

    //List of commands:
    //* MOVE - unit is moving to its destination
    //* SHOOT - unit shoots given target
    //* BUILD - factory builds unit
    //* SET_RALLY_POINT - factory sets new rally point
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

    void setCommand(enum Command command);
};
