#include "PlayerId.h"

PlayerId::PlayerId(std::string name) {
    this->name = name;
}

std::ostream& operator<<(std::ostream& os, const PlayerId& playerId) {
    os << playerId.name;
    return os;
}
