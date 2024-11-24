#pragma once

#include <exception>
#include <vector>
#include "Card.h"


class ParseFailed : public std::exception {
    std::string message;
public:
    ParseFailed(std::string message);

    const char* what() const throw();
};


Card parseCard(const std::string& input);
std::vector<Card> parseCards(const std::string& input);
