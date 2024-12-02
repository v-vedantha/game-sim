#include "Card.h"

class Deck {

public:
    Deck();

    std::vector<std::vector<Card>> getRunouts(int numCards);
};
