#include "pathfinding.h"
#include <cmath>

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
        float x_next = xst + ceil(speed * (xend - xst) / len);
        float y_next = yst + ceil(speed * (yend - yst) / len);

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

    return path;
}