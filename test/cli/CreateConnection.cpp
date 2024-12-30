#include "Server.h"
#include "Shell.h"
#include <gtest/gtest.h>
#include <iostream>
#include <thread>
using namespace cli;

TEST(CreateConnection, Success) {
    Context context;

    std::cout << "Hi" << std::endl;
    std::thread server(start_server);
    server.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Creating the command here" << std::endl;
    std::unique_ptr<Command> command = std::make_unique<CreateGame>();

    std::cout << "Running the command here" << std::endl;
    command->run(context);
};
