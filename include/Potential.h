#include "Card.h"
#include "Strength.h"
#include <map>

// Potential describes the hands that a player has a chance of making
// It is intended to be constructed by a player's HoleCards given the information they know
// about the board, and in the future maybe cards they think their oponent has.

class Potential {
public:
    double oddsOfHitting(Rank& rank);

    Potential(std::map<Rank, double> oddsOfHitting);
private:
    std::map<Rank, double> m_oddsOfHitting;
};

class PotentialBuilder {
public:
    PotentialBuilder();
    void addRunout(Rank rank);
    Potential buildPotential();

private:
    std::map<Rank, int> numRunoutsWithRank;
};
