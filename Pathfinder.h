#ifndef PATHFINDER_H
#define PATHFINDER_H

// Find the shortest number of steps from (startX, startY) to the exit (4,4)
// on a 5x5 grid using Dijkstra's algorithm.
// Returns the step count, or -1 if unreachable.
int findShortestPath(int startX, int startY);

#endif
