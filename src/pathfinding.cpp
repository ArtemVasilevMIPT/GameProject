#include "pathfinding.h"
#include <cmath>
#include <iostream>

NavMesh::NavMesh(size_t ox, size_t oy) {
    navMap.resize(ox);
    for(size_t i= 0; i < ox; ++i) {
        navMap[i].resize(oy);
    }
}
const std::vector<bool>& NavMesh::operator[](size_t x) const {
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

std::queue<std::pair<float, float>> NavComponent::findPath(std::pair<float, float> start, std::pair<float, float> finish, float speed) {
    float xst = start.first;
    float yst = start.second;
    float xend = finish.first;
    float yend = finish.second;

    std::queue<std::pair<float, float>> path;

    while(abs(xst - xend) >= EPSILON || abs(yst - yend) >= EPSILON) {
        float len = sqrt((xend - xst) * (xend - xst) + (yend - yst) * (yend - yst));
        if (len <= speed) {
            path.push({xend, yend});
            break;
        }
        float x_next = xst + speed * (xend - xst) / len;
        float y_next = yst + speed * (yend - yst) / len;

        if (!map[ceil(x_next)][ceil(y_next)]) {
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

            while (map[x_next][y_next])*/
        }
    }

    //std::cout << "start: " << start.first << ' ' << start.second << '\n';
    //std::cout << "finish: " << finish.first << ' ' << finish.second << '\n';
    /*
    std::queue<std::pair<float, float>> path1 = path;
    for (int i = 0; i < path.size(); ++i) {
        //std::cout << path1.front().first << ' ' << path1.front().second << '\n';
        path1.pop();
    }
     */

    return path;
}