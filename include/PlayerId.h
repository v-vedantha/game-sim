#pragma once
#include <string>

/**
 * @brief Players in a game are identified by unque PlayerIds. This class
 * implements enough of the hash/== operators to be used as the key in an
 * unordered_map
 *
 */
class PlayerId {
  public:
    /**
     * @brief Constructs a playerId with the name serving as a unique identified
     * for the player.
     *
     * @param name A unique string to identify this player.
     */
    PlayerId(std::string name);
    std::string name;

    /**
     * @brief Compare playerIds by their name.
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator==(const PlayerId &other) const {
        return this->name == other.name;
    }

    friend std::ostream &operator<<(std::ostream &os, const PlayerId &playerId);
};
std::ostream &operator<<(std::ostream &os, const PlayerId &playerId);
namespace std {
/* Implement std::hash<PlayerId> so PlayerId can be used as a key in an
 * unordered_map.
 */
template <> struct hash<PlayerId> {
    std::size_t operator()(const PlayerId &playerId) const {
        // Just use the hash of the players name.
        return std::hash<std::string>{}(playerId.name);
    }
};
} // namespace std
