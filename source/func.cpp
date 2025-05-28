#include "../header/blackjack.h"

// Account class

void Account::registerUser() {
    std::cout << "Enter name: ";
    std::cin >> name;
    tokenAmount = 1000;
    saveFile.open(fileName, std::ios::out);
    saveFile << name << std::endl << tokenAmount;
    saveFile.close();
}

void Account::saveBalance() {
    saveFile.open(fileName, std::ios::out);
    saveFile << name << std::endl << tokenAmount;
    saveFile.close();
}

bool Account::checkBalance() {
    return tokenAmount > 0;
}

void Account::placeBet() {
    while (!(std::cin >> betAmount) || betAmount <= 0 || betAmount > tokenAmount) {
        std::cout << "Invalid input. Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    tokenAmount -= betAmount;
    saveBalance();
}

char Account::DisplayMenu() {
    system("cls");
    std::cout << "User: " << name << std::endl
        << "Balance: " << tokenAmount << std::endl << std::endl
        << "Blackjack? " << std::endl 
        << "[0] Exit" << std::endl
        << "[1] Play" << std::endl << std::endl;
    return char(getch());
}

Account::Account() {
        std::string textLine;
        int lineIndicator = 1;

        saveFile.open(fileName, std::ios::in);
        if (saveFile.is_open()) {
            while (getline(saveFile, textLine)) {
                switch (lineIndicator) {
                    case 1:
                        name = textLine;
                        if (name.empty()) {
                            std::cout << "Couldn't resolve username, register again" << std::endl;
                            saveFile.close();
                            registerUser();
                        }
                        break;
                    case 2:
                        tokenAmount = std::atoi(textLine.c_str());
                        if (tokenAmount <= 0) {
                            std::cout << "Savings are either 0 or corrupted, register again" << std::endl;
                            saveFile.close();
                            registerUser();
                        }
                        break;
                    }
                    lineIndicator++;
                }
                saveFile.close();
        } else {
            registerUser();
        }
    }

// Hand class

void Hand::display(int cardNumber) {
    if (cardNumber == 0) {
        for (auto card : cards) {
            std::cout << card.first << card.second << "  ";
        }
    } else {
        for (int i = 0; i < cardNumber; i++) {
            std::cout << cards[i].first << cards[i].second << "  ";
        }
    }
}

void Hand::drawCard(Deck &deck) {
    cards.push_back(deck.drawCard());
}

int Hand::sum() {
    int sum = 0;
    int aceCount = 0;
    for (auto card : cards) {
        sum += cardValues.at(card.first);
        if (card.first == "A") {
            aceCount++;
        }
    }
    while (sum > 21 && aceCount > 0) {
        sum -= 10;
        aceCount--;
    }
    return sum;
}

bool Hand::checkForBj() {
    return cards.size() == 2 && sum() == 21;
}

void Hand::stand() {
    choseToStand = true;
}

void Hand::hit(Deck &deck) {
    drawCard(deck);
}

Hand::Hand() : choseToStand(false), hasWon(false) {}

// Hand (child) PlayerHand

bool PlayerHand::canDoubleDown() {
    return !doubledDown && (playerAccount.getBet() <= playerAccount.getToken()) && cards.size() == 2;
}

void PlayerHand::doubleDown() {
    playerAccount.setBet(playerAccount.getBet() * 2);
    doubledDown = true;
}

PlayerHand::PlayerHand(Account &acc) : playerAccount(acc), doubledDown(false) {};

// Deck Class

Deck::Deck() {
    for (auto suit : suits) {
        for (auto rank : ranks) {
            cards.emplace_back(rank, suit);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

std::pair<std::string, std::string> Deck::drawCard() {
    auto card = cards.back();
    cards.pop_back();
    return card;
}
