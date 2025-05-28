#ifndef DECK_H
#define DECK_H

#include "../blackjack.h"

class Deck {
private:
    std::vector<std::pair<std::string, std::string>> cards;
public:
    std::pair<std::string, std::string> drawCard();

    Deck();
};

#endif