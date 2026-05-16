#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "Item.h"
#include "../ds/BST.h"
#include "Enemy.h"
#include "../ds/Queue.h"
#include "Player.h"

enum RoomType { EMPTY, ENEMY, ITEM };

class Room {
public:
    Room();

    void     setType(RoomType t);
    RoomType getType() const;

    void displayRoomInfo() const;

    bool isVisited()      const;
    void setVisited(bool v);

    void triggerEvent(const std::vector<Item>& items, BST& inventory, Player& player);

private:
    RoomType type;
    bool     visited;
};

#endif
