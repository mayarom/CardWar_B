# War Card Game

A C++ simulation of the popular card game War, where two players draw cards from their decks and the player with the highest card wins.

## Game Rules

The game is played with a standard deck of 52 cards.

Each player is dealt half the deck, 26 cards each, face-down.

Both players reveal the top card from their deck at the same time.

The player with the higher card takes both cards and adds them to the bottom of their deck.

If both players reveal cards of the same rank, a "war" occurs:

- Both players draw one card face-down, and then another card face-up.
- The player with the higher second card takes all cards on the table (including the face-down cards) and adds them to the bottom of their deck.
- If the second cards are also equal, the process repeats until a player wins the war.

The game continues until one player has all the cards or until a predetermined number of rounds have been played.

## Objects

The game is implemented using the following classes:

- `Card` - represents a single card in the deck, with a rank and a suit.
- `Deck` - represents a deck of cards, with methods to shuffle and deal cards.
- `Player` - represents a player in the game, with a deck of cards and methods to draw and add cards.
- `Game` - represents the game itself, with two players, a deck of cards, and methods to play the game, keep track of the score, and print out the results.

## Usage

To run the simulation, compile the `Demo.cpp` file using a C++ compiler and execute the resulting program. The program will simulate a game of War and output the results to the console.

```bash
$ g++ Demo.cpp -o war
$ ./war
