#include "Shell.h"
#include <gtest/gtest.h>
using namespace cli;

TEST(CreateConnection, Success) {
    Context context;

    std::unique_ptr<Command> command = std::make_unique<CreateGame>();

    command->run(context);
};
