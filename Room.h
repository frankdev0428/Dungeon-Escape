#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "Item.h"
#include "InventoryBST.h"
#include "Enemy.h"

// The three possible types a room can be
enum RoomType {
    EMPTY,
    ENEMY,
    ITEM
};

class Room {
public:
    // Constructor — defaults to EMPTY if no type is given
    Room();

    void setType(RoomType t);   // change the room's type
    RoomType getType() const;   // read the room's type

    void displayRoomInfo() const; // print what kind of room this is

    bool isVisited() const;       // returns whether the room has been entered
    void setVisited(bool v);      // manually mark the room as visited/unvisited

    // Triggers the room event on first entry; does nothing on repeat visits.
    // items is passed in so ITEM rooms can pick a random one to display.
    // items   = pool to pick from
    // inventory = BST to insert the picked item into
    void triggerEvent(const std::vector<Item>& items, InventoryBST& inventory);

private:
    RoomType type;   // the room's current type
    bool visited;    // true once the player has entered this room
};

#endif
