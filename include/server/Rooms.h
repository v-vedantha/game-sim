#pragma once
#include "Room.h"
#include "RoomId.h"
#include <unordered_map>

class Rooms {
  public:
    RoomId createRoom();

  private:
    std::unordered_map<RoomId, Room> rooms;

    RoomIdCreator roomIdCreator;
};
