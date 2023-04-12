/** written by Maya Rom
 * id: 207485251
 * date: 27.03.2023
 */

#include "card.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

namespace ariel
{

    Card::Card() : rank(Rank::NO_RANK), suit(Suit::HEARTS) {}

    Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

    Card::Card(const Card &other) noexcept : rank(other.rank), suit(other.suit) {}

    Card::Card(Card &&other) noexcept : rank(other.rank), suit(other.suit) {}

    Card &Card::operator=(const Card &other) noexcept
    {
        if (this != &other)
        {
            rank = other.rank;
            suit = other.suit;
        }
        return *this;
    }

    Card &Card::operator=(Card &&other) noexcept
    {
        if (this != &other)
        {
            rank = other.rank;
            suit = other.suit;
        }
        return *this;
    }

    Card::~Card() {}

    std::string Card::toString() const
    {
        std::ostringstream out;
        std::string rankStr = "";
        std::string suitStr = "";
        int spaces = 0;

        if (rank == Rank::ACE)
        {
            rankStr += "A";
        }
        else if (rank == Rank::TWO)
        {
            rankStr += "2";
        }
        else if (rank == Rank::JACK)
        {
            rankStr += "J";
        }
        else if (rank == Rank::QUEEN)
        {
            rankStr += "Q";
        }
        else if (rank == Rank::KING)
        {
            rankStr += "K";
        }
        else
        {
            rankStr += std::to_string(static_cast<int>(rank));
        }

        switch (suit)
        {
        case Suit::HEARTS:
            suitStr += "♥";
            break;
        case Suit::SPADES:
            suitStr += "♠";
            break;
        case Suit::DIAMONDS:
            suitStr += "♦";
            break;
        case Suit::CLUBS:
            suitStr += "♣";
            break;
        }

        spaces = 7 - rankStr.size();
        out << "┌─────────┐\n";
        out << "│" << rankStr;
        for (int index = 0; index < spaces; index++)
        {
            out << " ";
        }
        out << "  |\n";
        out << "│         │\n";
        out << "│    " << suitStr << "    │\n";
        out << "│         │\n";
        spaces = 7 - std::to_string(static_cast<int>(rank)).size();
        out << "│   ";
        if (rank == Rank::ACE)
        {
            out << "1";
        }
        else
        {
            for (int index = 0; index < spaces; index++)
            {
                out << " ";
            }
            out << static_cast<int>(rank);
        }
        out << "    \n";
        out << "└─────────┘\n";

        return out.str();
    }

    // rank to string
    std::string getRankString(Rank rank)
    {
        std::string rankStr = "";
        if (rank == Rank::ACE)
        {
            rankStr += "A";
        }
        else if (rank == Rank::TWO)
        {
            rankStr += "2";
        }
        else if (rank == Rank::JACK)
        {
            rankStr += "J";
        }
        else if (rank == Rank::QUEEN)
        {
            rankStr += "Q";
        }
        else if (rank == Rank::KING)
        {
            rankStr += "K";
        }
        else
        {
            rankStr += std::to_string(static_cast<int>(rank));
        }
        return rankStr;
    }
    // suit to string
    std::string getSuitString(Suit suit)
    {
        std::string suitStr = "";
        switch (suit)
        {
        case Suit::HEARTS:
            suitStr += "♥";
            break;
        case Suit::SPADES:
            suitStr += "♠";
            break;
        case Suit::DIAMONDS:
            suitStr += "♦";
            break;
        case Suit::CLUBS:
            suitStr += "♣";
            break;
        }
        return suitStr;
    }

    std::string Card::toStringTwo(const Card &card1, const Card &card2)
    {
        std::string str;

        // Print top row
        str += "┌─────────┐  ┌─────────┐\n";

        // Print card 1
        str += "│";
        str += getRankString(card1.getRank());
        str += "        │  │";
        str += getRankString(card2.getRank());
        str += "        │\n";

        str += "│         │  │         │\n";
        str += "│    ";
        str += getSuitString(card1.getSuit());
        str += "    │  │    ";
        str += getSuitString(card2.getSuit());
        str += "    │\n";
        str += "│         │  │         │\n";
        str += "│        ";
        str += getRankString(card1.getRank());
        str += "│  │        ";
        str += getRankString(card2.getRank());
        str += "│\n";

        // Print bottom row
        str += "└─────────┘  └─────────┘\n";
        return str;
    }

    int Card::compare(const Card &other) const
    {
        if (rank == Rank::ACE && other.rank != Rank::ACE)
        {
            return 1;
        }
        else if (rank != Rank::ACE && other.rank == Rank::ACE)
        {
            return -1;
        }
        //two win ace
        else if (rank == Rank::TWO && other.rank != Rank::TWO)
        {
            return 1;
        }
        else if (rank != Rank::TWO && other.rank == Rank::TWO)
        {
            return -1;
        }
  
        else if (rank == other.rank)
        {
            return 0;
        }
        else if (rank > other.rank)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

} // namespace ariel
