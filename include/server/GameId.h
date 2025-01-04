#pragma once
#include <boost/json.hpp>
#include <string>

class GameId {
  public:
    GameId(std::string id);
    std::string id;

    bool operator==(const GameId &other) const { return this->id == other.id; }

    friend std::ostream &operator<<(std::ostream &os, const GameId &gameId);

    std::unique_ptr<boost::json::object> to_json();
};

std::ostream &operator<<(std::ostream &os, const GameId &gameId);
namespace std {
/* Implement std::hash<GameId> so GameId can be used as a key in an
 * unordered_map.
 */
template <> struct hash<GameId> {
    std::size_t operator()(const GameId &gameId) const {
        // Just use the hash of the players name.
        return std::hash<std::string>{}(gameId.id);
    }
};
} // namespace std
