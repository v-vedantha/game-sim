#pragma once 
#include "PlayerId.h"
#include <map>
#include <vector>

class WinningProbabilities {
public:
    WinningProbabilities(std::unordered_map<PlayerId, double> winningProbabilities);

    double getProbabilityOfWinning(PlayerId player);

private:
    std::unordered_map<PlayerId, double> winningProbabilities;
};

class WinningProbabilitiesBuilder {
public:
    WinningProbabilitiesBuilder(std::vector<PlayerId>);

    void addRunoutResult(const std::vector<PlayerId>& winners);

    WinningProbabilities winningProbabilities();

private:
    std::unordered_map<PlayerId, double> winningRunouts;
};
