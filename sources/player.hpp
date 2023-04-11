/** written by Maya Rom
 * id: 207485251
 * date: 27.03.2023
 */

#ifndef WAR_PLAYER_H
#define WAR_PLAYER_H

#include <string>
#include <vector>

#include "card.hpp"

namespace ariel
{
    struct PlayerStats
    {
        // initializing the stats:
        int cardsLeft = 0;
        int turnsPlayed = 0;
        int turnsWon = 0;
        int turnsLost = 0;
        int turnsDraw = 0;
    };

    class Player
    {
    private:
        std::vector<Card> cards_stack; 
        std::vector<Card> cards_taken;
        PlayerStats stats;
        std::string name;
        int cards_num = 0;

    public:
        // default constructor
        Player() = default;
        Player(const Player &other);
        Player &operator=(const Player &other);
        Player(std::string name);
        void addCard(const Card &card);
        void addTakenCard(const Card &card);
        Card playCard();
        int cardsLeft() const; // return the number of cards in the player's cards_stack
        std::string getName() const;
        void addTurnWon();
        void addTurnLost();
        void addTurnDraw();
        std::string getStats() const;
        int stacksize() const;
        int getTurnsWon() const;
        int getTurnsLost() const;
        int getTurnsDraw() const;
        int cardesTaken() const;
        //print cards_stack
        void printCardsStack() const;
        // destructor
        ~Player();

        // Move constructor
        Player(Player &&other) noexcept;

        // Move assignment operator
        Player &operator=(Player &&other) noexcept;
    };
} // namespace ariel

#endif // WAR_PLAYER_H
