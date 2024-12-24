#include <format>
#include <iostream>

#include "Card.h"
#include "CardParser.h"

ParseFailed::ParseFailed(std::string message) { this->message = message; }

const char *ParseFailed::what() const throw() { return message.c_str(); }

class TokenStream {
    std::string input;
    size_t currentTokenIdx;

  public:
    TokenStream(std::string input) {
        this->input = input;

        // Start at position 0
        this->currentTokenIdx = 0;
    }

    /**
     * @brief See the next token without consuming it.
     *
     * @return char The next token
     */
    char peek() {
        if (currentTokenIdx >= input.length()) {
            throw ParseFailed("Unexpected end of input");
        }
        return input[currentTokenIdx];
    }

    /**
     * @brief Peek nth tokens ahead without consuming it
     *
     * @param n  the number of tokens to look ahead
     * @throw ParseFailed if there are not enough tokens to look n ahead
     * @return char The token n tokens ahead, if it exists
     */
    char peek(int n) {
        if (currentTokenIdx + n >= input.length()) {
            throw ParseFailed("Unexpected end of input");
        }
        return input[currentTokenIdx + n];
    }

    /**
     * @brief Consumes the next token, returning it
     *
     * @return char The next token
     */
    char consume() {
        if (currentTokenIdx >= input.length()) {
            throw ParseFailed("Unexpected end of input");
        }
        return input[currentTokenIdx++];
    }

    /**
     * @brief Returns whether there are any additional tokens in the stream
     *
     * @return true There are more tokens in the stream
     * @return false The stream is exhausted. No tokens left.
     */
    bool hasNext() { return currentTokenIdx < input.length(); }
};

Suit parseSuit(TokenStream &stream) {
    // The tokens corresponding to each suit are shown below
    // Spades = S or s
    // Clubs = C or c
    // Diamonds = D or d
    // Hearts = H or h
    // (in general it is the first letter in the suit)
    char suit = stream.consume();
    switch (suit) {
    case 'H':
        return Suit::HEARTS;
    case 'D':
        return Suit::DIAMONDS;
    case 'C':
        return Suit::CLUBS;
    case 'S':
        return Suit::SPADES;
    case 'h':
        return Suit::HEARTS;
    case 'd':
        return Suit::DIAMONDS;
    case 'c':
        return Suit::CLUBS;
    case 's':
        return Suit::SPADES;
    default:
        throw ParseFailed(std::format(
            "Invalid suit: Got {} Expected H, D, C, S (or lower case)", suit));
    }
}

Value parseValue(TokenStream &stream) {
    // For the numeric cards, we can only parse their numeric values (i.e. 2-10)
    // For face cards, we only parse the first letter capitalized (J, Q, K, A)
    char firstChar = stream.consume();
    switch (firstChar) {
    case '2':
        return Value::TWO;
    case '3':
        return Value::THREE;
    case '4':
        return Value::FOUR;
    case '5':
        return Value::FIVE;
    case '6':
        return Value::SIX;
    case '7':
        return Value::SEVEN;
    case '8':
        return Value::EIGHT;
    case '9':
        return Value::NINE;
    case '1': {
        // If we see a 1, it can only mean the value was intended to be 10
        char secondChar = stream.consume();
        if (secondChar == '0') {
            return Value::TEN;
        } else {
            throw ParseFailed(std::format(
                "Invalid value: Expected a 0 after a 1", secondChar));
        }
    }
    case 'J':
        return Value::JACK;
    case 'Q':
        return Value::QUEEN;
    case 'K':
        return Value::KING;
    case 'A':
        return Value::ACE;
    default:
        throw ParseFailed(std::format(
            "Invalid value: Got {}Expected 2-9, J, Q, K, A", firstChar));
    }
}

Card parseCard(TokenStream &stream) {
    // Cards are meant to be formatter as ValueSuit

    // First parse the value. Note that this will throw an exception if the
    // value cannot be parsed.
    Value value = parseValue(stream);

    // Then parse the suit. Similarly will throw an exception if suit cannot be
    // parsed.
    Suit suit = parseSuit(stream);
    return Card(value, suit);
}

Card parseCard(const std::string &input) {
    TokenStream stream(input);
    return parseCard(stream);
}

std::vector<Card> parseCards(const std::string &input) {
    TokenStream stream(input);

    std::vector<Card> cards;
    while (stream.hasNext()) {
        // Any of these operations can throw, and since we dont catch it the
        // caller of parseCards must deal with it.
        // One improvement would be to return the cards we were able to parse in
        // case we get an error.
        cards.push_back(parseCard(stream));
    }
    return cards;
}
