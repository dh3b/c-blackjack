#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <map>
#include <algorithm>
#include <array>
#include <random>

#include "class/account.h"
#include "class/deck.h"
#include "class/hand.h"

class Account;
class Deck;
class Hand;
class PlayerHand;

const char fileName[17] = "Credentials.save";
const std::array<std::string, 4> suits = {"♥", "♦", "♣", "♠"};
const std::array<std::string, 13> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const std::map<std::string, short> cardValues = {
    {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6},
    {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"J", 10},
    {"Q", 10}, {"K", 10}, {"A", 11}
};

#endif 