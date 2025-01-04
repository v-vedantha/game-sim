#include "RoomId.h"
#include <boost/json.hpp>
#include <boost/json/src.hpp>

RoomId::RoomId(std::string id) { this->id = id; }

std::ostream &operator<<(std::ostream &os, const RoomId &roomId) {
    os << roomId.id;
    return os;
}

std::unique_ptr<boost::json::object> RoomId::to_json() {
    std::unique_ptr<boost::json::object> json_obj =
        std::make_unique<boost::json::object>();
    (*json_obj)["gameId"] = this->id;
    return json_obj;
}
