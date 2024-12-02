#include <unordered_map>


class PlayerOdds {
    double winningChance;

public:
    PlayerOdds(double winningChance);

    double getWinningChance();
};

class TableOdds {

    std::unordered_map<PlayerId, PlayerOdds> odds;

public:


};
