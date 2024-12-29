#pragma once
#include <string>

namespace cli {
/**
 * @brief Represents a connection from the client to a server.
 *
 */
class Connection {
  public:
    void sendMessage(const std::string &message);
};

} // namespace cli
