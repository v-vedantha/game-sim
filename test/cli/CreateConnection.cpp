#include "Server.h"
#include "Shell.h"
#include <gtest/gtest.h>
#include <iostream>
#include <thread>

using namespace cli;
using namespace server;

TEST(CreateConnection, Success) {
    Context context;

    std::thread server(start_server);
    server.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_ptr<Command> command = std::make_unique<CreateGame>();

    command->run(context);
};
