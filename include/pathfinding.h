#pragma once
#include <vector>
#include <queue>
#include "core.h"

const float EPSILON = 1e-5;


class NavComponent : public Component {
    NavMesh& map;

public:
    NavComponent(NavMesh& map) : map(map) {
        name = "NavComponent";
    };
    NavComponent(const NavComponent& another) = default;
    ~NavComponent() = default;

    std::queue<std::pair<float, float>> findPath(std::pair<float, float> start, std::pair<float, float> finish, float speed);
};