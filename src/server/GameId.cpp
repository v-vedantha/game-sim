#include "GameId.h"
#include <boost/json.hpp>

#include <boost/json/src.hpp>
GameId::GameId(std::string id) { this->id = id; }

std::ostream &operator<<(std::ostream &os, const GameId &gameId) {
    os << gameId.id;
    return os;
}
boost::json::value GameId::to_json() {
    boost::json::object json_obj;
    json_obj["gameId"] = this->id;
    return json_obj;
}
