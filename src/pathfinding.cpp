#include "pathfinding.h"
#include <cmath>

NavMesh::NavMesh(size_t ox, size_t oy) {
    navMap.resize(ox);
    for(size_t i= 0; i < ox; ++i) {
        navMap[i].resize(oy);
    }
}
const std::vector<bool> NavMesh::operator[](size_t x) const {
    return navMap[x];
}
void NavMesh::placeObstacle(std::pair<size_t, size_t> position, size_t size_x, size_t size_y) {
    for(size_t i = position.first; i < position.first + size_x; ++i) {
        for(size_t j = position.second; j < position.second + size_y; ++j) {
            navMap[i][j] = true;
        }
    }
}

void NavMesh::removeObstacle(std::pair<size_t, size_t> position, size_t size_x, size_t size_y) {
    for(size_t i = position.first; i < position.first + size_x; ++i) {
        for(size_t j = position.second; j < position.second + size_y; ++j) {
            navMap[i][j] = true;
        }
    }
}

std::queue<std::pair<size_t, size_t>> NavComponent::findPath(std::pair<float, float> start, std::pair<float, float> finish, float speed) {
    size_t xst = floor(start.first);
    size_t yst = floor(start.second);
    size_t xend = floor(finish.first);
    size_t yend = floor(finish.second);

    std::queue<std::pair<size_t, size_t>> path;

    while(xst != xend && yst != yend) {
        size_t len = sqrt((xend - xst) * (xend - xst) + (yend - yst) * (yend - yst));
        if (len >= speed) {
            path.push({xend, yend});
            break;
        }
        size_t x_next = speed * (xst - xend) / len;
        size_t y_next = speed * (yst - yend) / len;

        if (!map[floor(x_next)][y_next]) {
            path.push({x_next, y_next});
            xst = x_next;
            yst = y_next;
            continue;
        } else {
            break;
            /*int hflag = 0, vflag = 0;
            if (map[x_next][y_next + 1] || map[x_next][y_next - 1]) {
                if (xend >= xst) {
                    hflag = 1;
                } else {
                    hflag = -1;
                }
            }
            if (map[x_next + 1][y_next] || map[x_next - 1][y_next]) {
                if (yend >= yst) {
                    vflag = 1;
                } else {
                    vflag = -1;
                }
            }

            while (map[x_next][y_next])
        }*/
    }
    return path;
}