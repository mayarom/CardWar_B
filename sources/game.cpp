/** written by Maya Rom
 * id: 207485251
 * date: 27.03.2023
 */
#include "card.hpp"
#include "player.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include "game.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

// Define the escape sequences for colors
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

namespace ariel
{
    // constructors:

    // First constructor - by players:
    Game::Game(Player &first_player, Player &second_player) : winner(-1), player1(first_player), player2(second_player)
    {

        std::cout << CYAN << "   __    __    ___  _         __   ___   ___ ___    ___          ______   ___           ______  __ __    ___          __    __   ____  ____            ____   ____  ___ ___    ___ \n"
                  << "  |  |__|  |  /  _]| |       /  ] /   \\ |   |   |  /  _]        |      | /   \\         |      ||  |  |  /  _]        |  |__|  | /    ||    \\          /    | /    ||   |   |  /  _]\n"
                  << "  |  |  |  | /  [_ | |      /  / |     || _   _ | /  [_         |      ||     |        |      ||  |  | /  [_         |  |  |  ||  o  ||  D  )        |   __||  o  || _   _ | /  [_ \n"
                  << "  |  |  |  ||    _]| |___  /  /  |  O  ||  \\_/  ||    _]        |_|  |_||  O  |        |_|  |_||  _  ||    _]        |  |  |  ||     ||    /         |  |  ||     ||  \\_/  ||    _]\n"
                  << "  |  `  '  ||   [_ |     |/   \\_ |     ||   |   ||   [_           |  |  |     |          |  |  |  |  ||   [_         |  `  '  ||  _  ||    \\         |  |_ ||  _  ||   |   ||   [_ \n"
                  << "   \\      / |     ||     |\\     ||     ||   |   ||     |          |  |  |     |          |  |  |  |  ||     |         \\      / |  |  ||  .  \\        |     ||  |  ||   |   ||     |\n"
                  << "    \\_/\\_/  |_____||_____| \\____| \\___/ |___|___||_____|          |__|   \\___/           |__|  |__|__||_____|          \\_/\\_/  |__|__||__|\\_|        |___,_||__|__||___|___||_____|\n";

        std::cout << RESET;
        cout << "  " << endl;

        this->roundsPlayed = 0;
        cout << MAGENTA << "preparing the game...\n"
             << RESET << endl;
        // fill the middle stack with cards
        for (int rank = 1; rank < 14; rank++)
        {
            for (int suit = 0; suit < 4; suit++)
            {
                Suit cardSuit = static_cast<Suit>(suit);
                Rank cardRank = static_cast<Rank>(rank);
                Card card(cardRank, cardSuit);
                middle_stack.push_back(card);
            }
        }

        // suffle

        cout << YELLOW << "Shuffling the cards...\n"
             << RESET << endl;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(std::begin(middle_stack), std::end(middle_stack), gen);

        cout << GREEN << "Dealing the cards...\n"
             << RESET << endl;
        // split cards
        players[0] = &first_player;
        players[1] = &second_player;
        for (size_t i = 0; i < middle_stack.size(); i += 2)
        {
            players[0]->addCard(middle_stack[i]);
            players[1]->addCard(middle_stack[i + 1]);
        }
        // clear the middle stack
        middle_stack.clear();
        cout << CYAN << "--------------------  The game is ready  ------------------------\n"
             << RESET << endl;
    }

    //  default constructor
    Game::Game() : winner(-1), player1(*new Player("player1")), player2(*new Player("player2")) {}

    // move assignment operator (rvalue reference)
    Game &Game::operator=(Game &&other) noexcept
    {
        if (this != &other)
        {
            middle_stack = std::move(other.middle_stack);
            players[0] = std::move(other.players[1]);
            players[1] = std::move(other.players[2]);
            mainLog = std::move(other.mainLog);
            lastTurn = std::move(other.lastTurn);
            winner = other.winner;
            roundsPlayed = other.roundsPlayed;
        }
        return *this;
    }
    // Move constructor
    Game::Game(Game &&other) noexcept
        : middle_stack(std::move(other.middle_stack)),
          players(std::move(other.players)),
          player1(other.player1),
          player2(other.player2),
          mainLog(std::move(other.mainLog)),
          lastTurn(std::move(other.lastTurn)),
          winner(other.winner),
          roundsPlayed(other.roundsPlayed)
    {
    }
    // Copy constructor
    Game::Game(const Game &other)
        : middle_stack(other.middle_stack),
          player1(*other.players[0]),
          player2(*other.players[1]),
          mainLog(other.mainLog),
          lastTurn(other.lastTurn),
          winner(other.winner),
          roundsPlayed(other.roundsPlayed)
    {
        players = {&player1, &player2};
    }
    // Copy assignment operator
    Game &Game::operator=(const Game &other)
    {
        if (this != &other)
        {
            middle_stack = other.middle_stack;
            player1 = *other.players[0];
            player2 = *other.players[1];
            mainLog = other.mainLog;
            lastTurn = other.lastTurn;
            winner = other.winner;
            roundsPlayed = other.roundsPlayed;
            players = {&player1, &player2};
        }
        return *this;
    }

    // destructor:
    Game::~Game() {}

    // creating the cards and filling the middle_stack
    void Game::fillCards()
    {
        for (int rank = 1; rank <= 13; rank++)
        {
            for (int suit = 0; suit < 4; suit++)
            {
                Card card(static_cast<Rank>(rank), static_cast<Suit>(suit));
                middle_stack.push_back(card);
            }
        }
    }

    // shuffling the cards:
    void Game::shuffleDeck()
    {

        random_device rd;
        mt19937 g(rd());
        shuffle(this->middle_stack.begin(), this->middle_stack.end(), g);
    }

    // splitting the cards between the players:
    void Game::splitCards()
    {
        for (unsigned int i = 0; i < 52; i++)
        {
            if (i % 2 == 0)
            {
                player1.addCard(middle_stack[i]);
            }
            else
            {
                player2.addCard(middle_stack[i]);
            }
        }
    }
    void Game::playAll()

    {

        std::cout << "The game is started!" << std::endl;
        std::cout << "Now, each player has: " << player1.stacksize() << " cards" << std::endl;
        std::cout << "In the middle heap there are:  " << middle_stack.size() << " cards" << std::endl;
        while (winner == -1 && roundsPlayed < 27 && this->isFinished == false)
        {

            playTurn();
            checkWin();
        }
        checkWin();
    }

    // playing a turn:
    void Game::playTurn()
    {

        // error
        if (player1.getName() == player2.getName())
        {
            throw std::invalid_argument("Players cannot have the same name!");
        }

        roundsPlayed++;

        // print the turn number
        std::cout << "\033[1;36m--------------------------------------------\033[0m" << std::endl;
        std::cout << "\033[1;36m               Turn number: " << roundsPlayed << "\033[0m" << std::endl;
        std::cout << "\033[1;36m--------------------------------------------\033[0m" << std::endl;
        std::cout << "\n"
                  << std::endl;

        checkWin();

        // every player put in the middle stack the card
        middle_stack.push_back(player1.playCard());
        middle_stack.push_back(player2.playCard());

        // print the cards
        std::cout << player1.getName() << " card:   " << player2.getName() << " card: " << std::endl;
        std::cout << Card::toStringTwo(middle_stack[middle_stack.size() - 2], middle_stack[middle_stack.size() - 1]) << std::endl;

        // compare the cards - who wins the turn
        if (middle_stack[middle_stack.size() - 2].compare(middle_stack[middle_stack.size() - 1]) > 0) // player1 wins
        {
            player1.addTurnWon();
            player2.addTurnLost();
            mainLog += player1.getName() + " played:\n " + middle_stack[middle_stack.size() - 1].toString() + "\n" + player2.getName() + " played:\n " + middle_stack[middle_stack.size() - 2].toString() + "\n " + player1.getName() + " won the turn" + "\n\n";
            lastTurn = player1.getName() + " played:\n " + middle_stack[middle_stack.size() - 1].toString() + "\n" + player2.getName() + " played:\n " + middle_stack[middle_stack.size() - 2].toString() + "\n " + player1.getName() + " won the turn" + "\n\n";
            // Display the winner of the turn
            std::cout << "\033[1;32m" // Set text color to green
                      << "Winner of the turn: " << player1.getName()
                      << "\033[0m" // Reset text color to default
                      << std::endl;

            // add the cards to the winner

            player1.addTakenCard(middle_stack[middle_stack.size() - 2]);
            player1.addTakenCard(middle_stack[middle_stack.size() - 1]);

            checkWin();
            // clear the middle stack
            middle_stack.clear();
            // go back to the beginning of the function
            return;
        }
        else if (middle_stack[middle_stack.size() - 2].compare(middle_stack[middle_stack.size() - 1]) < 0) // player1 wins // player2 wins
        {
            player2.addTurnWon();
            // print the winner of the turn
            // Display the winner of the turn
            mainLog += player1.getName() + " played:\n " + middle_stack[middle_stack.size() - 1].toString() + "\n" + player2.getName() + " played: \n" + middle_stack[middle_stack.size() - 1].toString() + "\n" + player2.getName() + " won the turn" + "\n\n";
            lastTurn = player1.getName() + " played:\n " + middle_stack[middle_stack.size() - 1].toString() + "\n" + player2.getName() + " played: \n" + middle_stack[middle_stack.size() - 1].toString() + "\n" + player2.getName() + " won the turn" + "\n\n";
            std::cout << "\033[1;32m" // Set text color to green
                      << "Winner of the turn: " << player2.getName()
                      << "\033[0m" // Reset text color to default
                      << std::endl;

            // add the cards to the winner
            player2.addTakenCard(middle_stack[middle_stack.size() - 2]);
            player2.addTakenCard(middle_stack[middle_stack.size() - 1]);

            checkWin();
            // clear the middle stack
            middle_stack.clear();
            // go back to the beginning of the function
            return;
        }
        // if the cards are equal - war
        {
            // print middle size
            checkWin();
            // update the draw counter
            player1.addTurnDraw();
            player2.addTurnDraw();
            mainLog += player1.getName() + " played :\n" + middle_stack[middle_stack.size() - 1].toString() + "\n" + player2.getName() + " played:\n " + middle_stack[middle_stack.size() - 1].toString() + " \n" + "It's a... war!" + "\n\n";
            lastTurn = player1.getName() + " played :\n" + middle_stack[middle_stack.size() - 1].toString() + "\n" + player2.getName() + " played:\n " + middle_stack[middle_stack.size() - 1].toString() + " \n" + "It's a... war!" + "\n\n";
            // tie_war();
            std::cout << GREEN << "tie! we are starting a...                " << endl;
            std::cout << " __    __              " << std::endl;
            std::cout << "/ / /\\ \\ \\  __ _  _ __ " << std::endl;
            std::cout << "\\ \\/  \\/ / / _` || '__|" << std::endl;
            std::cout << " \\  /\\  / | (_| || |   " << std::endl;
            std::cout << "  \\/  \\/   \\__,_||_|   " << std::endl;
            std::cout << "                      " << std::endl;
            std::cout << "Are you ready??\n"
                      << RESET << std::endl;

            // declare the cards
            int tie_seq = 1;

            while (player1.stacksize() > 0 && player2.stacksize() > 0)
            {

                roundsPlayed++;
                // print the turn number
                std::cout << "\033[1;36m--------------------------------------------\033[0m" << std::endl;
                std::cout << "\033[1;36m               Turn number: " << roundsPlayed << "\033[0m" << std::endl;
                std::cout << "\033[1;36m--------------------------------------------\033[0m" << std::endl;
                // print the tie sequence
                // prints how many cards each player has
                std::cout << player1.getName() << " has " << player1.stacksize() << " cards left" << std::endl;
                std::cout << player2.getName() << " has " << player2.stacksize() << " cards left" << std::endl
                          << std::endl;

                std::cout << "Tie sequence: " << tie_seq << std::endl;

                // every player put in the middle stack two cards

                for (int i = 0; i < 2; i++)
                {
                    if (player1.stacksize() == 0 || player2.stacksize() == 0)
                    {
                        while (middle_stack.size() > 0)
                        {
                            player1.addTakenCard(middle_stack[middle_stack.size() - 1]);
                            middle_stack.pop_back();
                            player2.addTakenCard(middle_stack[middle_stack.size() - 1]);
                            middle_stack.pop_back();
                        }
                        break;
                    }
                    middle_stack.push_back(player1.playCard());
                    middle_stack.push_back(player2.playCard());
                }

                // print the the last two cards
                std::cout << "The last two open cards are:" << std::endl;
                std::cout << player1.getName() << " card:   " << player2.getName() << " card: " << std::endl;
                std::cout << Card::toStringTwo(middle_stack[middle_stack.size() - 2], middle_stack[middle_stack.size() - 1]) << std::endl
                          << std::endl;

                // compare the cards - who wins the turn

                // if player1 wins
                if (middle_stack[middle_stack.size() - 2].compare(middle_stack[middle_stack.size() - 1]) > 0)
                {
                    player1.addTurnWon();

                    // Display the winner of the turn
                    std::cout << "\033[1;32m" // Set text color to green
                              << "Winner of the turn: " << player1.getName()
                              << "\033[0m" // Reset text color to default
                              << std::endl;

                    for (int i = 0; i < middle_stack.size(); i++)
                    {
                        player1.addTakenCard(middle_stack[static_cast<std::vector<Card>::size_type>(i)]);
                    }

                    middle_stack.clear();
                    mainLog += player1.getName() + " played: \n" + middle_stack[middle_stack.size() - 2].toString() + "\n" + player2.getName() + " played: \n" + middle_stack[middle_stack.size() - 1].toString() + " \n " + player1.getName() + " won the turn" + "\n\n";
                    lastTurn = player1.getName() + " played: \n" + middle_stack[middle_stack.size() - 2].toString() + "\n" + player2.getName() + " played: \n" + middle_stack[middle_stack.size() - 1].toString() + " \n " + player1.getName() + " won the turn" + "\n\n";
                    checkWin();
                    break;
                }

                // the winner of the turn is player2
                else if (middle_stack[middle_stack.size() - 2].compare(middle_stack[middle_stack.size() - 1]) < 0)
                {
                    player2.addTurnWon();
                    // print the winner of the turn
                    // Display the winner of the turn
                    std::cout << "\033[1;32m" // Set text color to green
                              << "Winner of the turn: " << player2.getName()
                              << "\033[0m" // Reset text color to default
                              << std::endl;

                    for (int i = 0; i < middle_stack.size(); i++)
                    {
                        player2.addTakenCard(middle_stack[static_cast<std::vector<Card>::size_type>(i)]);
                    }
                    middle_stack.clear();
                    mainLog += player1.getName() + " played :\n" + middle_stack[middle_stack.size() - 2].toString() + "\n" + player2.getName() + " played: \n " + middle_stack[middle_stack.size() - 1].toString() + " \n" + player2.getName() + " won the turn" + "\n\n";
                    lastTurn = player1.getName() + " played :\n" + middle_stack[middle_stack.size() - 2].toString() + "\n" + player2.getName() + " played: \n " + middle_stack[middle_stack.size() - 1].toString() + " \n" + player2.getName() + " won the turn" + "\n\n";
                    checkWin();
                    break;
                }
                else // if the cards are equal - continue
                {
                    checkWin();
                    // update the draw counter
                    player1.addTurnDraw();
                    player2.addTurnDraw();
                    mainLog += player1.getName() + " played:\n " + middle_stack[middle_stack.size() - 2].toString() + "\n" + player2.getName() + " played:\n " + middle_stack[middle_stack.size() - 1].toString() + " - " + "WAR" + "\n\n";
                    tie_seq++;
                    lastTurn = player1.getName() + " played:\n " + middle_stack[middle_stack.size() - 2].toString() + "\n" + player2.getName() + " played:\n " + middle_stack[middle_stack.size() - 1].toString() + " - " + "WAR" + "\n\n";
                }
            }
            checkWin();
        }
    }
    void Game::printLastTurn()
    {
        if (roundsPlayed == 0)
        {
            std::cout << "No turns have been played yet." << std::endl;
        }
        else
        {
            std::cout << "\033[1m    __             __    ______               \033[0m" << std::endl;
            std::cout << "\033[1m   / /  ___ _ ___ / /_  /_  __/__ __ ____ ___ \033[0m" << std::endl;
            std::cout << "\033[1m  / /__/ _ `/(_-</ __/   / /  / // // __// _ \\ \033[0m" << std::endl;
            std::cout << "\033[1m /____/\\_,_//___/\\__/   /_/   \\_,_//_/  /_//_/ \033[0m" << std::endl;
            std::cout << "\033[1m                                               \033[0m" << std::endl;

            // print last turn
            std::cout << "\033[1;36m--------------------------------------------\033[0m" << std::endl;
            std::cout << "\033[1;36m               Turn number: " << roundsPlayed << "\033[0m" << std::endl;
            std::cout << "\033[1;36m--------------------------------------------\033[0m" << std::endl;
            cout << lastTurn << endl;
        }
    }
    void Game::printWiner()
    {
        if (player1.stacksize() == 0 || player2.stacksize() == 0 || roundsPlayed == 26)
        {

            if (player1.cardesTaken() > player2.cardesTaken())
            {
                std::cout << GREEN << "\033[1m                                                    \033[0m" << std::endl;
                std::cout << "\033[1m" << GREEN << " _____  _           _ _ _  _                     \033[0m" << std::endl;
                std::cout << "\033[1m" << GREEN << "|_   _|| |_  ___   | | | ||_| ___  ___  ___  ___ \033[0m" << std::endl;
                std::cout << "\033[1m" << GREEN << "  | |  |   || -_|  | | | || ||   ||   || -_||  _| \033[0m" << std::endl;
                std::cout << "\033[1m" << GREEN << "  |_|  |_|_||___|  |_____||_||_|_||_|_||___||_|  \033[0m" << std::endl;
                std::cout << "\033[1m                                                    \033[0m" << RESET << std::endl;

                std::cout << "\033[1;32m" // Set text color to green
                          << "             *** " << player1.getName() << " ***\n"
                          << "\033[0m" // Reset text color to default
                          << std::endl;
                std::cout << "\033[1;35m";

                std::cout << "            '._==_==_=_.'            " << endl;
                std::cout << "            .-\\:      /-.           " << endl;
                std::cout << "           | (|:.     |) |           " << endl;
                std::cout << "            '-|:.     |-'            " << endl;
                std::cout << "            '-|:.     |-'            " << endl;
                std::cout << "            '-|:.     |-'            " << endl;
                std::cout << "              \\::.    /              " << endl;
                std::cout << "               '::. .'               " << endl;
                std::cout << "                 ) (                 " << endl;
                std::cout << "               _.' '._               " << endl;
                std::cout << "              '-------'              " << RESET << endl;
                // print line
                std ::cout << "   Thank you for playing! Until next time...\n"
                           << endl;

                std::cout << "\033[0m";
            }
            else if (player1.cardesTaken() < player2.cardesTaken())
            {

                std::cout << GREEN << "\033[1m                                                    \033[0m" << std::endl;
                std::cout << "\033[1m" << GREEN << " _____  _           _ _ _  _                     \033[0m" << std::endl;
                std::cout << "\033[1m" << GREEN << "|_   _|| |_  ___   | | | ||_| ___  ___  ___  ___ \033[0m" << std::endl;
                std::cout << "\033[1m" << GREEN << "  | |  |   || -_|  | | | || ||   ||   || -_||  _| \033[0m" << std::endl;
                std::cout << "\033[1m" << GREEN << "  |_|  |_|_||___|  |_____||_||_|_||_|_||___||_|  \033[0m" << std::endl;
                std::cout << "\033[1m                                                    \033[0m" << RESET << std::endl;
                std::cout << "\033[1;32m" // Set text color to green
                          << "             *** " << player2.getName() << " ***\n"
                          << "\033[0m" // Reset text color to default
                          << std::endl;
                std::cout << "\033[1;35m";

                std::cout << "            '._==_==_=_.'            " << endl;
                std::cout << "            .-\\:      /-.           " << endl;
                std::cout << "           | (|:.     |) |           " << endl;
                std::cout << "            '-|:.     |-'            " << endl;
                std::cout << "            '-|:.     |-'            " << endl;
                std::cout << "            '-|:.     |-'            " << endl;
                std::cout << "              \\::.    /              " << endl;
                std::cout << "               '::. .'               " << endl;
                std::cout << "                 ) (                 " << endl;
                std::cout << "               _.' '._               " << endl;
                std::cout << "              '-------'              " << RESET << endl;
                // print line
                std ::cout << "   Thank you for playing! Until next time...\n"
                           << endl;

                std::cout << "\033[0m";
            }
            else
            {

                std::cout << YELLOW;
                std::cout << "   _________   _____   ________  " << std::endl;
                std::cout << "  |  _   _  | |_   _| |_   __  | " << std::endl;
                std::cout << "  |_/ | | \\_|   | |     | |_ \\_| " << std::endl;
                std::cout << "      | |       | |     |  _| _  " << std::endl;
                std::cout << "     _| |_     _| |_   _| |__/ | " << std::endl;
                std::cout << "    |_____|   |_____| |________| " << std::endl;
                std::cout << std::endl;
                std::cout << RESET << "The game ended in a tie!" << std::endl;
            }
        }
        else
        {
            std::cout << "\033[1;31m" // Set text color to red
                      << "No winner declared yet!"
                      << "\033[0m" // Reset text color to default
                      << std::endl;
        }
    }

    // printing the log:
    void Game::printLog()
    {
        if (mainLog.empty())
        {
            std::cout << "No log entries to print." << std::endl;
            return;
        }

        std::cout << "                                       _                 \n"
                  << "                                      | |                \n"
                  << "   __ _    __ _   _ __ ___     ___    | |   ___     __ _ \n"
                  << "  / _` |  / _` | | '_ ` _ \\   / _ \\   | |  / _ \\   / _` |\n"
                  << " | (_| | | (_| | | | | | | | |  __/   | | | (_) | | (_| |\n"
                  << "  \\__, |  \\__,_| |_| |_| |_|  \\___|   |_|  \\___/   \\__, |\n"
                  << "   __/ |                                            __/ |\n"
                  << "  |___/                                            |___/ \n";
        std::cout << std::endl
                  << mainLog;
    }

    // Member function to get the winner
    const Player &Game::getWinner() const
    {
        if (winner == 1)
        {
            return *players[0];
        }
        else if (winner == 2)
        {
            return *players[1];
        }
        else
        {
            throw std::logic_error("No winner declared yet!");
        }
    }

    void Game::printStats()
    {

        const int NUM_PLAYERS = 2;

        std::cout << BLUE << " _____                                     _____   _             _     _         _     _              " << RESET << std::endl;
        std::cout << RED << "/ ____|                                   / ____| | |           | |   (_)       | |   (_)             " << RESET << std::endl;
        std::cout << GREEN << "| |  __    __ _   _ __ ___     ___        | (___   | |_    __ _  | |_   _   ___  | |_   _    ___   ___ " << RESET << std::endl;
        std::cout << YELLOW << "| | |_ |  / _` | | '_ ` _ \\   / _ \\        \\___ \\  | __|  / _` | | __| | | / __| | __| | |  / __| / __|" << RESET << std::endl;
        std::cout << MAGENTA << "| |__| | | (_| | | | | | | | |  __/        ____) | | |_  | (_| | | |_  | | \\__ \\ | |_  | | | (__  \\__ \\" << RESET << std::endl;
        std::cout << CYAN << " \\_____|  \\__,_| |_| |_| |_|  \\___|       |_____/   \\__|  \\__,_|  \\__| |_| |___/  \\__| |_|  \\___| |___/" << RESET << std::endl;
        std::cout << std::endl;

        if (middle_stack.size() > 0)
        {
            // divide it between the players
            while (middle_stack.size() > 0)
            {
                player1.addTakenCard(middle_stack[middle_stack.size() - 1]);
                if (middle_stack.size() >= 1)
                    player2.addTakenCard(middle_stack[middle_stack.size() - 2]);
            }
            middle_stack.clear();
        }
        // Celebrate the rounds played
        cout << "--------------------------------------------------------" << endl;

        cout << YELLOW << "Congratulations to all players for playing " << this->roundsPlayed << " rounds!" << RESET << endl;
        cout << "--------------------------------------------------------" << endl
             << endl;

        // Introduce the players
        cout << "Let's give a round of applause to our amazing players:" << endl;
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            Player player = (i == 0) ? player1 : player2;
            cout << "   - " << player.getName() << endl;
        }
        cout << "--------------------------------------------------------" << endl
             << endl;

        // Reveal the rounds results
        cout << "Now, let's see how many rounds each player won:" << endl;
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            Player player = (i == 0) ? player1 : player2;
            cout << "   - " << player.getName() << " won " << player.getTurnsWon() << " rounds" << endl;
        }
        cout << "And there were " << player1.getTurnsDraw() << " ties!" << endl;
        cout << "--------------------------------------------------------" << endl
             << endl;

        // Display the remaining cards
        cout << "After all those rounds, here's how many cards each player has left:" << endl;
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            Player player = (i == 0) ? player1 : player2;
            cout << "   - " << player.getName() << " has " << player.stacksize() << " cards left" << endl;
        }
        cout << "in the middle card heap, there are " << middle_stack.size() << " cards" << endl;

        cout << "--------------------------------------------------------" << endl
             << endl;

        // Announce the final results
        cout << "And finally, the moment we've all been waiting for..." << endl;
        for (int i = 0; i < NUM_PLAYERS; i++)
        {
            Player player = (i == 0) ? player1 : player2;
            cout << "   - " << player.getName() << " took " << player.cardesTaken() << " cards in total!" << endl;
        }
        cout << endl;
        cout << "--------------------------------------------------------" << endl
             << endl;
    }

    // returning the log:
    std::string Game::getLog()
    {
        return mainLog;
    }

    // checking if the game is over- if one of the players has no cards or if pass 26 rounds:
    void Game::checkWin()
    {
        // if pass 26 round or one of the players has no cards
        if (roundsPlayed > 26 || player1.stacksize() == 0 || player2.stacksize() == 0)
        {

            int p = 1;
            // divide it between the players
            int sum = player1.cardesTaken();
            sum += player2.cardesTaken();
            sum += player1.stacksize();
            sum += player2.stacksize();
            while ((middle_stack.size() > 0) && (sum < 52))
            {

                if (p == 1)
                {

                    player1.addTakenCard(middle_stack[middle_stack.size() - 1]);
                    p = 2;
                    // remove the card from the middle stack
                    middle_stack.pop_back();
                }
                else
                {
                    player2.addTakenCard(middle_stack[middle_stack.size() - 1]);
                    p = 1;
                    // remove the card from the middle stack
                    middle_stack.pop_back();
                }
            }

            middle_stack.clear();

            // print line
            cout << "--------------------------------------------------------" << endl;
            cout << MAGENTA << "*** The game is over after " << roundsPlayed << " turns ***" << endl;
            // finish the game
            isFinished = true;

            cout << "--------------------------------------------------------" << endl;

            if (player1.cardesTaken() > player2.cardesTaken())
            {
                winner = 0;
                printWiner();
            }
            else if (player1.cardesTaken() < player2.cardesTaken())
            {
                winner = 1;
                printWiner();
            }
            else
            {
                winner = 5;
                printWiner();
            }
        }
        // if no winner yet
        else
        {
            winner = -1;
            return; // no winner yet - continue the game
        }
    }

} // namespace war
