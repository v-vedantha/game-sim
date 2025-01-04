#pragma once
#include <boost/json.hpp>
#include <string>

class RoomId {
  public:
    RoomId(std::string id);
    std::string id;

    bool operator==(const RoomId &other) const { return this->id == other.id; }

    friend std::ostream &operator<<(std::ostream &os, const RoomId &gameId);

    std::unique_ptr<boost::json::object> to_json();
};

std::ostream &operator<<(std::ostream &os, const RoomId &gameId);
namespace std {
/* Implement std::hash<GameId> so GameId can be used as a key in an
 * unordered_map.
 */
template <> struct hash<RoomId> {
    std::size_t operator()(const RoomId &gameId) const {
        // Just use the hash of the players name.
        return std::hash<std::string>{}(gameId.id);
    }
};
} // namespace std
