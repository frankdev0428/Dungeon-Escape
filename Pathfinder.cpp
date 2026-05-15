#include <iostream>
#include <vector>
#include <queue>    // priority_queue
#include <climits>  // INT_MAX
#include "Pathfinder.h"

const int DX[] = { 1, -1,  0, 0 };
const int DY[] = { 0,  0,  1, -1 };

int findShortestPath(int startX, int startY, int gridRows, int gridCols, int exitX, int exitY) {
    const int EXIT_X = exitX;
    const int EXIT_Y = exitY;

    // Use a 2D vector so size is determined at runtime
    std::vector<std::vector<int>> dist(gridRows,
        std::vector<int>(gridCols, INT_MAX));

    dist[startY][startX] = 0;

    typedef std::pair<int, std::pair<int,int>> Entry;
    std::priority_queue<Entry,
                        std::vector<Entry>,
                        std::greater<Entry>> pq;
    pq.push({0, {startX, startY}});

    while (!pq.empty()) {
        Entry current = pq.top();
        pq.pop();

        int d = current.first;
        int x = current.second.first;
        int y = current.second.second;

        if (d > dist[y][x]) continue;
        if (x == EXIT_X && y == EXIT_Y) break;

        for (int i = 0; i < 4; i++) {
            int nx = x + DX[i];
            int ny = y + DY[i];

            if (nx < 0 || nx >= gridCols || ny < 0 || ny >= gridRows) continue;

            int newDist = d + 1;
            if (newDist < dist[ny][nx]) {
                dist[ny][nx] = newDist;
                pq.push({newDist, {nx, ny}});
            }
        }
    }

    int result = dist[EXIT_Y][EXIT_X];
    return (result == INT_MAX) ? -1 : result;
}
