#include <core.h>
#include <vector>
#include <queue>

const float EPSILON = 1e-5;

class NavMesh {
    std::vector<std::vector<bool>> navMap;
public:

    NavMesh(size_t ox, size_t oy);
    ~NavMesh() = default;

    const std::vector<bool>& operator[](size_t x) const;

    void placeObstacle(std::pair<size_t, size_t> position, size_t size_x, size_t size_y);
    void removeObstacle(std::pair<size_t, size_t> position, size_t size_x, size_t size_y);
};

class NavComponent : public Component {
    NavMesh& map;

public:
    NavComponent(NavMesh& map) : map(map) {
        name = "NavComponent";
    };
    ~NavComponent() = default;

    std::queue<std::pair<float, float>> findPath(std::pair<float, float> start, std::pair<float, float> finish, float speed);
};