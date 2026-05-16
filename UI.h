#ifndef UI_H
#define UI_H

#include "Player.h"
#include "Map.h"

void printTitle();                          // game title banner
void printHUD(const Player& player, int stepsToExit, int roomsVisited, int totalRooms);
void printMap(const Map& map, const Player& player);  // formatted grid
void printMenu();                           // command reference

#endif
