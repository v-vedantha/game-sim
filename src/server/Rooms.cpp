#include "Rooms.h"

RoomId Rooms::createRoom() {
    RoomId roomId = roomIdCreator.createRoomId();

    rooms[roomId] = Room();

    return roomId;
}
