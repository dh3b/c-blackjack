#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../blackjack.h"

class Account {
private:
    std::fstream saveFile;
    std::string name;
    int tokenAmount, betAmount;
public:
    void registerUser();
    void saveBalance();
    bool checkBalance();
    void placeBet();
    char DisplayMenu();

    std::string getName() const { return name; }
    int getToken() const { return tokenAmount; }
    int getBet() const { return betAmount; }
    
    void setToken(int token) { tokenAmount = token; } 
    void setBet(int bet) { betAmount = bet; }

    Account();
};

#endif