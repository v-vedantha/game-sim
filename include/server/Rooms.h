#pragma once
#include "RoomId.h"
#include <unordered_map>

class Rooms {
  public:
    RoomId createRoom();

  private:
    // std::unordered_map<RoomId, Room> games;
};
