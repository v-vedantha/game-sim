#include "PlayerId.h"
#include <memory>


class Game;

class Player {
public:
    Player(PlayerId id, int chips);
    void join(std::shared_ptr<Game> game);

    // Poker actions
    void call();
    void check(); 
    void raise(int amount);
    void reraise(int amount);
    void allIn();

    void addChips(int amount);
    int stack();

    PlayerId id;

private:
    std::shared_ptr<Game> game;

    int chips;
};
