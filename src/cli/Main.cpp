#include "Command.h"
#include "Context.h"
#include "Shell.h"

using namespace cli;
void main_loop() {
    bool done = false;
    Context context;
    Shell shell;
    while (!done) {
        shell.refresh();
        Command command = shell.userCommand();
        command.run(context);
    }
}
int main() { main_loop(); }
