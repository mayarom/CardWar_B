#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <string>

namespace ariel
{
    enum class Rank
    {
        ACE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        NO_RANK
    };

    enum class Suit
    {
        HEARTS,
        SPADES,
        DIAMONDS,
        CLUBS
    };

    class Card
    {
    public:
        Card();

        // Constructor
        Card(Rank rank, Suit suit);

        // Copy constructor
        Card(const Card &other) noexcept;

        // Move constructor
        Card(Card &&other) noexcept;

        // Copy assignment operator
        Card &operator=(const Card &other) noexcept;

        // Move assignment operator
        Card &operator=(Card &&other) noexcept;

        // Destructor
        ~Card();

        // Returns a string representation of the card
        std::string toString() const;
        static std::string toStringTwo(const Card &card1, const Card &card2);

        // Compare this card to another card, and return a value indicating which is higher
        int compare(const Card &other) const;

        // Getters
        Rank getRank() const { return rank; }
        Suit getSuit() const { return suit; }

        // Setters
        void setRank(Rank rank) { this->rank = rank; }
        void setSuit(Suit suit) { this->suit = suit; }

        // Static methods
        static std::string suitToString(Suit suit);
        static std::string rankToString(Rank rank);

    private:
        Rank rank;
        Suit suit;
    };
} // namespace ariel

#endif // CARD_HPP
