#pragma once
#include <string>

class PlayerId {
    public:
        PlayerId(std::string name);
        std::string name;

        bool operator==(const PlayerId& other) const {
            return this->name == other.name;
        }

        friend std::ostream& operator<<(std::ostream& os, const PlayerId& playerId);
};
std::ostream& operator<<(std::ostream& os, const PlayerId& playerId);
namespace std {
    template <>
    struct hash<PlayerId> {
        std::size_t operator()(const PlayerId& playerId) const {
            return std::hash<std::string>{}(playerId.name);
        }
    };
}
