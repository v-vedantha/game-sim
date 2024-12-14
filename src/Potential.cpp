#include "Potential.h"
#include "Strength.h"
#include <iostream>
#include <map>

PotentialBuilder::PotentialBuilder() {
    for (Rank rank : allRanks) {
        numRunoutsWithRank[rank] = 0;
    }
}


void PotentialBuilder::addRunout(Rank rank) {
    numRunoutsWithRank[rank]++;
}

Potential PotentialBuilder::buildPotential() {
    int numRunouts = 0.0;
    for (auto it = numRunoutsWithRank.begin(); it != numRunoutsWithRank.end(); it++) {
        numRunouts += it->second;
    }

    std::map<Rank, double> oddsOfHitting;

    for (auto it = numRunoutsWithRank.begin(); it != numRunoutsWithRank.end(); it++) {
        oddsOfHitting[it->first] =  (1.0 * it->second) / numRunouts;
    }
    
    return Potential(oddsOfHitting);
}


Potential::Potential(std::map<Rank, double> oddsOfHitting) { 
    m_oddsOfHitting = oddsOfHitting;
}

double Potential::oddsOfHitting(Rank& rank) {
    return m_oddsOfHitting[rank];
}
