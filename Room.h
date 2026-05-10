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

    bool isVisited() const;       // returns whether the room has been entered
    void setVisited(bool v);      // manually mark the room as visited/unvisited

    // Triggers the room event on first entry; does nothing on repeat visits
    void triggerEvent();

private:
    RoomType type;   // the room's current type
    bool visited;    // true once the player has entered this room
};

#endif
