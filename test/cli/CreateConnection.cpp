#include "HttpListener.h"
#include "Server.h"
#include "Shell.h"
#include <gtest/gtest.h>
#include <iostream>
#include <thread>

using namespace cli;
using namespace server;

TEST(CreateConnection, Success) {
    Context context;
    std::shared_ptr<Server> server = std::make_shared<Server>();

    std::thread listener(start_listener, server);
    listener.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_ptr<Command> command = std::make_unique<CreateGame>();

    command->run(context);
};
