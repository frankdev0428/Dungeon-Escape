#ifndef DISPLAY_H
#define DISPLAY_H

#include "../core/Player.h"
#include "../core/Map.h"

void printTitle();
void printHUD(const Player& player, int stepsToExit, int roomsVisited, int totalRooms);
void printMap(const Map& map, const Player& player);
void printMenu();

#endif
