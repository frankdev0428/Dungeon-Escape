#ifndef PATHFINDER_H
#define PATHFINDER_H

// Find the shortest number of steps from (startX, startY) to the exit
// (gridSize-1, gridSize-1) using Dijkstra's algorithm.
// Returns the step count, or -1 if unreachable.
int findShortestPath(int startX, int startY, int gridRows, int gridCols);

#endif
