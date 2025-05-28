#include "../header/blackjack.h"

bool playBlackjack(Account &playerAccount);

int main() {
    SetConsoleOutputCP(65001);

    Account playerAccount;
    char menuChoice = '1';
    int winStreak = 0;

    // Display menu and start the game
    while (menuChoice) {
        menuChoice = playerAccount.DisplayMenu();
        switch (menuChoice) {
            case '0':
                return 0;
            case '1':
                if (!playerAccount.checkBalance()) playerAccount.registerUser();
                srand(static_cast<unsigned int>(time(nullptr)));
                std::cout << "Win streak: " << winStreak;
                playBlackjack(playerAccount) ? winStreak++ : winStreak = 0; 
                system("pause");
                break;
            default:
                std::cout << "Please choose between 0 and 1" << std::endl;
                Sleep(1000);
                break;
        }
    }

    return 0;
}


bool playBlackjack(Account &playerAccount) {
    PlayerHand playerHand(playerAccount);
    Hand dealerHand;
    Deck cardDeck;

    bool gameEnded = false;
    char playChoice;

    std::cout << std::endl << "Please place your bets: ";
    playerAccount.placeBet();

    // Draw two cards for both player and dealer
    for (int i = 0; i < 2; i++) {
        playerHand.drawCard(cardDeck);
        dealerHand.drawCard(cardDeck);
    }

    while (!gameEnded) {
        system("cls");

        // Determine who won, after the player chose to stand
        if (playerHand.getChoseToStand()) {
            while (dealerHand.sum() < 17) {
                dealerHand.drawCard(cardDeck);
            }

            if (dealerHand.sum() > 21) {
                playerHand.setHasWon(true);
            } else if (dealerHand.sum() > playerHand.sum()) {
                dealerHand.setHasWon(true);
            } else if (playerHand.sum() > dealerHand.sum()) {
                playerHand.setHasWon(true);
            } else {
                dealerHand.setHasWon(false);
                playerHand.setHasWon(false);
            }
            gameEnded = true;
        }

        // Determine who won, if the game is cut short
        if (!gameEnded) {
            if (dealerHand.checkForBj()) {
                dealerHand.setHasWon(true);
                gameEnded = true;
            } else if (playerHand.checkForBj()) {
                dealerHand.setHasWon(false);
                gameEnded = true;
            } else if (playerHand.sum() > 21) {
                dealerHand.setHasWon(true);
                gameEnded = true;
            }
        }
        
        // Display bet and hands
        std::cout << playerAccount.getName() << "'s bet: " << playerAccount.getBet() << std::endl;
        std::cout << "Dealer's hand: ";
        if (!gameEnded) {
            dealerHand.display(1);
            std::cout << "covered";
        } else dealerHand.display();
        std::cout << std::endl;
        std::cout << "Your hand: "; playerHand.display(); std::cout << std::endl;

        // Display summary after the game ends
        if (gameEnded) {
            if (playerHand.getHasWon()) {
                std::cout << playerAccount.getName() << " wins!" << std::endl;
                std::cout << "+ " << 2 * playerAccount.getBet() << std::endl;
                playerAccount.setToken(playerAccount.getToken() + 2 * playerAccount.getBet());
            } else if (dealerHand.getHasWon()) {
                std::cout << "Dealer wins!" << std::endl;
                std::cout << "- " << playerAccount.getBet() << std::endl;
                playerAccount.setToken(playerAccount.getToken() - playerAccount.getBet());
            } else {
                std::cout << "Tie with dealer" << std::endl;
                std::cout << "+ " << playerAccount.getBet() << std::endl;
                playerAccount.setToken(playerAccount.getToken() + playerAccount.getBet());
            }

            playerAccount.saveBalance();
            return playerHand.getHasWon();
        }

        // Get player's choice
        std::cout << std::endl << "Choice: [1] Stand [2] Hit";
        if (playerHand.canDoubleDown()) std::cout << " [3] Double down";
        std::cout << std::endl;

        playChoice = char(getch());
        switch (playChoice) {
            case '1':
                playerHand.stand();
                break;
            case '2':
                playerHand.hit(cardDeck);
                break;
            case '3':
                if (playerHand.canDoubleDown()) playerHand.doubleDown();
                break;
            default:
                std::cout << "Invalid choice. Please choose again.";
                Sleep(300);
                break;
        }
    }
    return false;
}

