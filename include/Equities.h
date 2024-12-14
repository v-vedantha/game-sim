#pragma once 
#include "PlayerId.h"
#include <map>
#include <vector>

class Equities {
public:
    Equities(std::unordered_map<PlayerId, double> equities);

    double getEquity(PlayerId player);

private:
    std::unordered_map<PlayerId, double> equities;
};

class EquitiesBuilder {
public:
    EquitiesBuilder(std::vector<PlayerId>);

    void addRunoutResult(const std::vector<PlayerId>& winners);

    Equities equities();

private:
    std::unordered_map<PlayerId, double> winningRunouts;
};
