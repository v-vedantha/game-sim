#pragma once
#include <string>

namespace cli {
/**
 * @brief Represents a connection from the client to a server.
 *
 */
class Connection {
  public:
    Connection();
    int sendMessage(const std::string &message);
};

} // namespace cli
