#include "RoomId.h"
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <stdexcept>

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

std::string generateRandomString(int length) {
    // Define the characters to use in the random string
    const std::string characters =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Random number generator and distribution
    std::random_device rd;        // Seed
    std::mt19937 generator(rd()); // Mersenne Twister generator
    std::uniform_int_distribution<> dist(0, characters.size() - 1);

    // Generate the random string
    std::string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += characters[dist(generator)];
    }

    return randomString;
}

RoomId RoomIdCreator::createRoomId() {
    int length = 7;
    RoomId out = RoomId(generateRandomString(length));
    int remainingTries = 8;
    while (existingRooms.find(out) != existingRooms.end()) {
        remainingTries--;
        if (remainingTries < 0) {
            throw new std::runtime_error("Could not create new roomId");
        }
        out = RoomId(generateRandomString(length));
    }

    return out;
}
