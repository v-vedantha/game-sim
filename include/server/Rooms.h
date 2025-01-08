#pragma once
#include "Endpoint.h"
#include "Room.h"
#include "RoomId.h"
#include <memory>
#include <unordered_map>
#include <vector>

class Rooms {
  public:
    RoomId createRoom();

  private:
    std::unordered_map<RoomId, Room> rooms;

    RoomIdCreator roomIdCreator;
};

class RoomsController {
  private:
    std::shared_ptr<Rooms> rooms;

  public:
    RoomsController();

    std::vector<std::shared_ptr<Endpoint>> endpoints();
};
