#include "Potential.h"
#include "Strength.h"
#include <cassert>
#include <iostream>
#include <map>

PotentialBuilder::PotentialBuilder() {
    // Initially no runouts are simulated
    for (Rank rank : allRanks) {
        numRunoutsWithRank[rank] = 0;
    }
}

void PotentialBuilder::addRunout(Rank rank) { numRunoutsWithRank[rank]++; }

Potential PotentialBuilder::buildPotential() {
    int numRunouts = 0.0;
    for (auto it = numRunoutsWithRank.begin(); it != numRunoutsWithRank.end();
         it++) {
        numRunouts += it->second;
    }

    // Avoid division by zero errors if someone forgot to add any runouts.
    assert(numRunouts > 0.1);

    std::unique_ptr<std::map<Rank, double>> oddsOfHitting =
        std::make_unique<std::map<Rank, double>>();

    // The odds of hitting a particular rank is the number of runouts which you
    // hit that rank / the number of runouts simulated
    for (auto it = numRunoutsWithRank.begin(); it != numRunoutsWithRank.end();
         it++) {
        oddsOfHitting->insert({it->first, 1.0 * it->second / numRunouts});
    }

    return Potential(std::move(oddsOfHitting));
}

Potential::Potential(std::unique_ptr<std::map<Rank, double>> oddsOfHitting) {
    // We should probably validate the the odds of hittin each rank are in the
    // range 0-1 and sum to 1.0.
    this->m_oddsOfHitting = std::move(oddsOfHitting);
}

double Potential::oddsOfHitting(Rank rank) { return m_oddsOfHitting->at(rank); }
