#pragma once
#include "PlayerId.h"
#include "TableCards.h"
#include "Bets.h"
#include <memory> 
#include <map>

class Player;

class Game {

public:

    void addPlayer(std::shared_ptr<Player> player);

    void finish();


    void dealToNextStreet();

    PlayerId nextIdToAct();

    // Should always match nextIdToAct so technically unnecessary
    // but it is useful to be confident that the game is in a consistent state.
    void check(PlayerId playerId);
    int call(PlayerId playerId);
    void raise(PlayerId playerId, int amount);
    void reraise(PlayerId playerId, int amount);
    void allIn(PlayerId playerId, int amount);


    Game(std::vector<std::weak_ptr<Player>> players);

private:
    std::vector<std::weak_ptr<Player>> players;

    std::unordered_map<PlayerId, std::weak_ptr<Player>> playersById;
    TableCards tableCards;

    // Game owns playersInHand
    std::shared_ptr<PlayersInHand> playersInHand;

    Bets bets;

    Street street;

};

class GameBuilder {
public:
    void addPlayer(std::shared_ptr<Player> player);
    std::shared_ptr<Game> build();
private:
    std::vector<std::weak_ptr<Player>> players;
};
