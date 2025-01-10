#include "Rooms.h"
#include "Uri.h"

RoomId Rooms::createRoom() {
    RoomId roomId = roomIdCreator.createRoomId();

    rooms[roomId] = Room();

    return roomId;
}

RoomsController::RoomsController() { rooms = std::make_shared<Rooms>(); }

class CreateRoomEndpoint : public Endpoint {
  private:
    std::shared_ptr<Rooms> m_rooms;
    Uri m_uri;
    http::verb m_verb;

  public:
    CreateRoomEndpoint(std::shared_ptr<Rooms> rooms) {
        m_rooms = rooms;
        m_uri = Uri("/games");
        m_verb = http::verb::post;
    }

    virtual bool canHandle(std::string &uri, http::verb verb) override {
        if (m_verb != verb) {
            return false;
        }
        return m_uri.canParse(uri);
    }

    virtual void handle(const http::request<http::string_body> &req,
                        http::response<http::string_body> &res) override {

        res.result(http::status::ok);
        RoomId roomId = m_rooms->createRoom();
        res.body() = boost::json::serialize(*(roomId.to_json()));
    }
};

std::vector<std::shared_ptr<Endpoint>> RoomsController::endpoints() {
    std::vector<std::shared_ptr<Endpoint>> routes;
    routes.push_back(std::make_shared<CreateRoomEndpoint>(rooms));

    return routes;
}
