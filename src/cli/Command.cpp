#include "Command.h"
#include "Context.h"

using namespace cli;
void Command::run(Context &context) {
    throw std::runtime_error("Must be implemented by children.");
}
void CreateGame::run(Context &context) {
    context.connection->sendMessage("hi");
}
