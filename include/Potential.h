#include "Card.h"
#include "Strength.h"
#include <map>


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
