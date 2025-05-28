#ifndef HAND_H
#define HAND_H

#include "../blackjack.h"

class Hand {
protected:
    std::vector<std::pair<std::string, std::string>> cards;
    bool choseToStand;
    bool hasWon;
public:
    void display(int cardNumber = 0);
    void drawCard(Deck &deck);
    int sum();
    bool checkForBj();

    void stand();
    void hit(Deck &deck);

    bool getHasWon() const { return hasWon; }
    bool getChoseToStand() const { return choseToStand; }

    void setHasWon(bool win) { hasWon = win; }

    Hand();
};

class PlayerHand : public Hand {
private:
    Account &playerAccount;
    bool doubledDown;
public:
    bool canDoubleDown();
    void doubleDown();

    PlayerHand(Account &acc);
};

#endif