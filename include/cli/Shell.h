#include "Command.h"
#include <iostream>
#include <string>

namespace cli {
/**
 * @brief When playing the game via the CLI, the user enters input/sees game
 * state and messages through a custom shell. This class is responsible for
 * maintaining the state of this custom shell.
 *
 */
class Shell {
  public:
    /**
     * @brief Refreshes the screen. Removes any old content, and redisplays new
     * content.
     *
     */
    void refresh();

    /**
     * @brief Returns the user's command.
     *
     */
    Command userCommand();
};
} // namespace cli
