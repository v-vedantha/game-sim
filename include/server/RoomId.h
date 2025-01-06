#pragma once
#include <boost/json.hpp>
#include <random>
#include <string>
#include <unordered_set>

class RommIdCreator;
class RoomId {
  private:
    RoomId(std::string id);
    std::string id;

  public:
    bool operator==(const RoomId &other) const { return this->id == other.id; }

    friend std::ostream &operator<<(std::ostream &os, const RoomId &gameId);

    std::unique_ptr<boost::json::object> to_json();

    friend class RoomIdCreator;
    friend struct std::hash<RoomId>;
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

class RoomIdCreator {
  public:
    /**
     * @brief Creates a roomId. Ensures roomIds are never duplicated.
     *
     * @return RoomId A unique roomId
     * @throw Can throw if we fail to generate a unique roomId
     */
    RoomId createRoomId();

  private:
    std::unordered_set<RoomId> existingRooms;
};
