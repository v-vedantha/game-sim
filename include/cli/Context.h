#pragma once

#include <Connection.h>
#include <memory>

namespace cli {
class Context {

  public:
    std::unique_ptr<Connection> connection;
};
} // namespace cli
