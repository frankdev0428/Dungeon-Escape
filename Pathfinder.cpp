#include <iostream>
#include <queue>    // priority_queue
#include <climits>  // INT_MAX
#include "Pathfinder.h"

const int GRID  = 5;
const int EXIT_X = 4;
const int EXIT_Y = 4;

// The four directions a player can move: right, left, down, up
const int DX[] = { 1, -1,  0, 0 };
const int DY[] = { 0,  0,  1, -1 };

int findShortestPath(int startX, int startY) {

    // --- Step 1: distance table ---
    // dist[row][col] = fewest steps needed to reach that cell.
    // Start with INT_MAX ("not yet reached") for every cell.
    int dist[GRID][GRID];
    for (int row = 0; row < GRID; row++)
        for (int col = 0; col < GRID; col++)
            dist[row][col] = INT_MAX;

    // The starting cell costs 0 steps to reach
    dist[startY][startX] = 0;

    // --- Step 2: min-heap priority queue ---
    // Stores {distance, {x, y}}.
    // std::greater makes it a MIN heap — smallest distance is processed first.
    // (Default priority_queue is a MAX heap, which would be wrong here.)
    typedef std::pair<int, std::pair<int,int>> Entry;
    std::priority_queue<Entry,
                        std::vector<Entry>,
                        std::greater<Entry>> pq;

    pq.push({0, {startX, startY}});

    // --- Step 3: Dijkstra loop ---
    while (!pq.empty()) {

        // Pop the cell with the smallest known distance
        Entry current = pq.top();
        pq.pop();

        int d = current.first;
        int x = current.second.first;
        int y = current.second.second;

        // If we already found a shorter path to this cell, skip it
        if (d > dist[y][x]) continue;

        // Early exit — we reached (4,4), no need to explore further
        if (x == EXIT_X && y == EXIT_Y) break;

        // --- Step 4: check all four neighbors ---
        for (int i = 0; i < 4; i++) {
            int nx = x + DX[i]; // neighbor column
            int ny = y + DY[i]; // neighbor row

            // Skip if out of grid bounds
            if (nx < 0 || nx >= GRID || ny < 0 || ny >= GRID) continue;

            // Every move costs 1 step
            int newDist = d + 1;

            // Only update if we found a shorter path to this neighbor
            if (newDist < dist[ny][nx]) {
                dist[ny][nx] = newDist;
                pq.push({newDist, {nx, ny}});
            }
        }
    }

    // --- Step 5: return result ---
    int result = dist[EXIT_Y][EXIT_X];
    if (result == INT_MAX) return -1; // exit was unreachable
    return result;
}
