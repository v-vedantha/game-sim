#include "WinningProbabilities.h"
#include <cassert>
#include <map>

WinningProbabilities::WinningProbabilities(std::unordered_map<PlayerId, double> winningProbabilities) {
    this->winningProbabilities = winningProbabilities;
}

double WinningProbabilities::getProbabilityOfWinning(PlayerId player) {
    return this->winningProbabilities.at(player);
}


WinningProbabilitiesBuilder::WinningProbabilitiesBuilder(std::vector<PlayerId> players) {
    for (const PlayerId& player : players) {
        this->winningRunouts[player] = 0;
    }
}

void WinningProbabilitiesBuilder::addRunoutResult(const std::vector<PlayerId>& winners) {
    for (const PlayerId& player : winners) {
        this->winningRunouts[player] += 1.0 / winners.size();
    }
}

WinningProbabilities WinningProbabilitiesBuilder::winningProbabilities() {
    std::unordered_map<PlayerId, double> winningProbabilities;
    double totalRunouts = 0.0;
    for (auto it = this->winningRunouts.begin(); it != this->winningRunouts.end(); it++) {
        totalRunouts += it->second;
    }
    assert(totalRunouts > 0.01);
    for (auto it = this->winningRunouts.begin(); it != this->winningRunouts.end(); it++) {
        winningProbabilities[it->first] = it->second / totalRunouts;
    }

    return WinningProbabilities(winningProbabilities);
}
