#pragma once
#include "Context.h"
#include <iostream>
#include <string>

namespace cli {
class Command {

  public:
    /**
     * @brief Runs the command with the given context.
     */
    virtual void run(Context &context);
};

class CreateGame : public Command {

  public:
    /**
     * @brief Creates a new game.
     *
     * @param context
     */
    void run(Context &context) override;
};

} // namespace cli
