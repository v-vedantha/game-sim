#pragma once

#include "Card.h"
#include <exception>
#include <vector>

/**
 * @class ParseFailed
 * @brief Exception thrown when parsing a card or a collection of cards fails.
 */
class ParseFailed : public std::exception {
    /**
     * @brief The error message describing the parsing failure.
     */
    std::string message;

  public:
    /**
     * @brief Constructs a ParseFailed exception with a specific error message.
     *
     * @param message A descriptive message explaining the reason for the
     * parsing failure.
     */
    ParseFailed(std::string message);

    /**
     * @brief Retrieves a description of the parsing failure.
     *
     * @return A C-style string containing the exception message.
     */
    const char *what() const throw();
};

/**
 * @brief Parses a single card from a string input.
 *
 * Example inputs: "10s", "AH".
 *
 * @param input A string representing a single card.
 * @return A `Card` object representing the parsed card.
 * @throws ParseFailed if the input is invalid or cannot be parsed.
 */
Card parseCard(const std::string &input);

/**
 * @brief Parses multiple cards from a string input.
 *
 * The input should be a list of card representations, such as
 * "ASKH10D" for Ace of Spades, King of Hearts, and Ten of Diamonds.
 *
 * @param input A string representing multiple cards.
 * @return A vector of `Card` objects representing the parsed cards.
 * @throws ParseFailed if the input is invalid or cannot be parsed.
 */
std::vector<Card> parseCards(const std::string &input);
