#pragma once
#include <vector>
#include <queue>
#include "core.h"

const float EPSILON = 1e-5;


class NavComponent : public Component
{
private:
    //Serialization stuff
    friend class boost::serialization::access;
    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        boost::serialization::base_object<Component>(*this);
        ar & map;
    }
    //
public:
    static NavMesh map;
    NavComponent()
    {
        name = "NavComponent";
    }
    /*
    NavComponent(NavMesh& map){
        name = "NavComponent";
    };
    */
    NavComponent(const NavComponent& another) = default;
    ~NavComponent() = default;

    std::queue<std::pair<float, float>> findPath(std::pair<float, float> start, std::pair<float, float> finish, float speed);
};