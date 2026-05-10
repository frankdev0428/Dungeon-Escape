#ifndef ROOM_H
#define ROOM_H

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

private:
    RoomType type; // the room's current type
};

#endif
