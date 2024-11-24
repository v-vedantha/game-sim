#include <iostream>
#include <format>

#include "Card.h"
#include "CardParser.h"

ParseFailed::ParseFailed(std::string message) {
    this->message = message;
}

const char* ParseFailed::what() const throw() {
    return message.c_str();
}

class TokenStream {
    std::string input;
    size_t currentTokenIdx;
public:
    TokenStream(std::string input) {
        this->input = input;
        this->currentTokenIdx = 0;
    }

    char peek() {
        if (currentTokenIdx >= input.length()) {
            throw ParseFailed("Unexpected end of input");
        }
        return input[currentTokenIdx];
    }

    char peek(int n) {
        if (currentTokenIdx + n >= input.length()) {
            throw ParseFailed("Unexpected end of input");
        }
        return input[currentTokenIdx + n];
    }

    char consume() {
        if (currentTokenIdx >= input.length()) {
            throw ParseFailed("Unexpected end of input");
        }
        return input[currentTokenIdx++];
    }

    bool hasNext() {
        return currentTokenIdx < input.length();
    }
};



Suit parseSuit(TokenStream& stream) {
    char suit = stream.consume();
    switch (suit) {
        case 'H':
            return HEARTS;
        case 'D':
            return DIAMONDS;
        case 'C':
            return CLUBS;
        case 'S':
            return SPADES;
        case 'h':
            return HEARTS;
        case 'd':
            return DIAMONDS;
        case 'c':
            return CLUBS;
        case 's':
            return SPADES;
        default:
            throw ParseFailed(std::format("Invalid suit: Got {} Expected H, D, C, S (or lower case)", suit));
    }
}

Value parseValue(TokenStream& stream) {
    char firstChar = stream.consume();
    switch (firstChar) {
        case '2':
            return TWO;
        case '3':
            return THREE;
        case '4':
            return FOUR;
        case '5':
            return FIVE;
        case '6':
            return SIX;
        case '7':
            return SEVEN;
        case '8':
            return EIGHT;
        case '9':
            return NINE;
        case '1':
            { 
                char secondChar = stream.consume();
                if (secondChar == '0') {
                    return TEN;
                }
                else {
                    throw ParseFailed(std::format("Invalid value: Expected a 0 after a 1", secondChar));
                }
            }
        case 'J':
            return JACK;
        case 'Q':
            return QUEEN;
        case 'K':
            return KING;
        case 'A':
            return ACE;
        default:
            throw ParseFailed(std::format("Invalid value: Got {}Expected 2-9, J, Q, K, A", firstChar));
    }
}

Card parseCard(TokenStream& stream) {
    Value value = parseValue(stream);
    Suit suit = parseSuit(stream);
    return Card(value, suit);
}


Card parseCard(const std::string& input) {
    TokenStream stream(input);
    return parseCard(stream);
}

std::vector<Card> parseCards(const std::string& input) {
    TokenStream stream(input);

    std::vector<Card> cards;
    while (stream.hasNext()) {
        cards.push_back(parseCard(stream));
    }
    return cards;
}
