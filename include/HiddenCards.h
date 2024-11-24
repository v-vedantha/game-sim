#pragma once

#include <array>
#include "Card.h"

class HiddenCards {
private:
    std::array<Card, 2> cards;

public:
    HiddenCards(std::array<Card, 2> cards);
}
