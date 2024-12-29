#include "Shell.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace cli;
void Shell::refresh() { system("clear"); }

Command Shell::userCommand() {
    std::string input;

    std::cout << "> ";
    std::cin >> input;

    Command command = CreateGame();

    return command;
}
