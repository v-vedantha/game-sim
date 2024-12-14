#include "Equities.h"
#include <cassert>
#include <map>

Equities::Equities(std::unordered_map<PlayerId, double> equities) {
    this->equities = equities;
}

double Equities::getEquity(PlayerId player) {
    return this->equities.at(player);
}


EquitiesBuilder::EquitiesBuilder(std::vector<PlayerId> players) {
    for (const PlayerId& player : players) {
        this->winningRunouts[player] = 0;
    }
}

void EquitiesBuilder::addRunoutResult(const std::vector<PlayerId>& winners) {
    for (const PlayerId& player : winners) {
        this->winningRunouts[player] += 1.0 / winners.size();
    }
}

Equities EquitiesBuilder::equities() {
    std::unordered_map<PlayerId, double> equities;
    double totalRunouts = 0.0;
    for (auto it = this->winningRunouts.begin(); it != this->winningRunouts.end(); it++) {
        totalRunouts += it->second;
    }
    assert(totalRunouts > 0.01);
    for (auto it = this->winningRunouts.begin(); it != this->winningRunouts.end(); it++) {
        equities[it->first] = it->second / totalRunouts;
    }

    return Equities(equities);
}
