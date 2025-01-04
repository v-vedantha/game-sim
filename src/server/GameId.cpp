#include "GameId.h"
#include <boost/json.hpp>
#include <boost/json/src.hpp>

GameId::GameId(std::string id) { this->id = id; }

std::ostream &operator<<(std::ostream &os, const GameId &gameId) {
    os << gameId.id;
    return os;
}

std::unique_ptr<boost::json::object> GameId::to_json() {
    std::unique_ptr<boost::json::object> json_obj =
        std::make_unique<boost::json::object>();
    (*json_obj)["gameId"] = this->id;
    return json_obj;
}
