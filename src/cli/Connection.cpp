#include "Connection.h"
#include <iostream>

using namespace cli;

void Connection::sendMessage(const std::string &message) {
    std::cout << message << std::endl;
}
