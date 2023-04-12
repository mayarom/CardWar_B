
/** written by Maya Rom
 * id: 207485251
 * date: 06.04.23
 */

#include <stdexcept>
#include "player.hpp"
#include "card.hpp"

using namespace std;
using namespace ariel;

// copy constructor
Player::Player(const Player &other)
    : name(other.name), cards_stack(other.cards_stack), stats(other.stats), cards_taken(other.cards_taken)
{
}

// Move assignment operator
Player &Player::operator=(Player &&other) noexcept
{
    if (this != &other)
    {
        name = other.name;
        cards_stack = other.cards_stack;
        stats = other.stats;
        cards_taken = other.cards_taken;
    }
    return *this;
}
    // Move constructor
    Player::Player(Player &&other) noexcept
    : name(other.name), cards_stack(other.cards_stack), stats(other.stats), cards_taken(other.cards_taken)
{
}

// second constructor- deep copy constructor:
Player &Player::operator=(const Player &other)
{
    if (this != &other)
    {
        name = other.name;
        cards_stack = other.cards_stack;
        stats = other.stats;
    }
    cout << "Player " << name << " was created!" << endl;
    return *this;
}
// third constructor - by name
Player::Player(string name)
{
    
    if (name.empty())
    {
        throw invalid_argument("Player name cannot be empty!");
    }
    
    this->name = name;
    this->cards_stack = vector<Card>();
    this->stats = PlayerStats();
    this->cards_taken = vector<Card>();

    cout << "Player " << name << " was created!" << endl;
}

// destructor - delete the player when the game is over
Player::~Player()
{
   
}

// add cards to the player's cards_stack
void Player::addTakenCard(const Card &card)
{

    cards_taken.push_back(card);
}
void Player::addCard(const Card &card)
{

    this->cards_stack.push_back(card);
    cards_num++;
}

// return the card at the top of the player's stack
Card Player::playCard()
{
    // call check winner function

    if (cards_stack.empty())
    {
        // the game is over
        throw invalid_argument("Player " + name + " has no more cards!");
    }
    Card card = cards_stack.front();        // get the card from the top of the stack
    cards_stack.erase(cards_stack.begin()); // remove the card from the stack
    return card;
}

// return the number of cards that the player has left
int Player::cardsLeft() const
{
    return cards_stack.size();
}

string Player::getName() const
{
    return this->name;
}

// counting the turns that the player won and play
void Player::addTurnWon()
{
    this->stats.turnsPlayed++;
    this->stats.turnsWon++;
}

// counting the turns that the player lost and play
void Player::addTurnLost()
{
    this->stats.turnsPlayed++;
    this->stats.turnsLost++;
}

// counting the turns that the player draw and play
void Player::addTurnDraw()
{
    this->stats.turnsPlayed++;
    this->stats.turnsDraw++;
}

// return the player's information
string Player::getStats() const
{

    string statsStr = "Player " + name + " stats:\n";
    statsStr += "Cards left: " + to_string(stats.cardsLeft) + "\n";
    statsStr += "Turns played: " + to_string(stats.turnsPlayed) + "\n";
    statsStr += "Turns won: " + to_string(stats.turnsWon) + "\n";
    statsStr += "Turns lost: " + to_string(stats.turnsLost) + "\n";
    statsStr += "Turns draw: " + to_string(stats.turnsDraw) + "\n";
    return statsStr;
}

// return the number of cards that the player has left
int Player::stacksize() const
{
    int size = cards_stack.size();
    return size;
}

// return the number of turns that the player won
int Player::getTurnsWon() const
{
    return stats.turnsWon;
}

// return the number of turns that the player lost
int Player::getTurnsLost() const
{
    return stats.turnsLost;
}

// return the number of turns that ended in a draw
int Player::getTurnsDraw() const
{
    return stats.turnsDraw;
}

// return the amount of cards this player has won.
int Player::cardesTaken() const
{
    return this->cards_taken.size();
}

void Player::printCardsStack() const
{
    if (cards_stack.empty())
    {
        cout << "Player " << name << " has no more cards!" << endl;
        return;
    }
    cout << "Player " << name << " cards stack:" << endl;
    for (std::vector<Card>::size_type i = 0; i < cards_stack.size(); i++)
    {
        cout << cards_stack[i].toString() << endl;
    }
}
