#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <random>
#include <iostream>

// Enumeration representing the player's turn.
enum class Round
{
   ROUND_PLAYER1,
   ROUND_PLAYER2
};

class Game
{
protected:
   /* ************************************************** */
   // Nested class representing a player in the game.
   class Player
   {
   private:
      char sign; // The player's sign (e.g., 'X' or 'O').

   public:
      // explicit: prevents unwanted implicit conversions.
      explicit Player(char s) : sign(s) {}

      // Returns the player's sign.
      char getSign() const { return sign; }
   };
   /* ************************************************** */

private:
   /* ************************************************** */
   static const int dim = 3;          // Dimension of the TicTacToe board.
   std::array<char, dim * dim> board; // The game board stored as a 1D array.

   Player player1; // Instance representing player 1.
   Player player2; // Instance representing player 2.

   // Initializes the game board with default values.
   void initBoard();
   // Prints the current state of the game board.
   void printBoard() const;

   // Randomly generates which player starts first.
   Round generateFirstRound();

   // Checks if any row contains a winning condition.
   bool checkRowsWinner() const;
   // Checks if any column contains a winning condition.
   bool checkColumnsWinner() const;
   // Checks if the main diagonal contains a winning condition.
   bool checkFirstDiagonalWinner() const;
   // Checks if the secondary diagonal contains a winning condition.
   bool checkSecondDiagonalWinner() const;
   // Checks if any diagonal contains a winning condition.
   bool checkDiagonalsWinner() const;
   // Checks if there is any winning condition on the board.
   bool checkWinner() const;

   // Validates whether the chosen position is valid for the current move.
   bool checkPosition(const size_t &pos, Round &curr_round) const;
   // Prompts the current player to input a board position.
   void askPosition(size_t &pos, Round &curr_round);
   // Updates the board at the specified position with the current player's sign.
   void updateBoard(const size_t &pos, Round &curr_round);
   // Switches the turn to the other player.
   void updateRound(Round &curr_round);

   /* ************************************************** */

public:
   /* ************************************************** */
   // Constructor: accepts signs for both players, initializes the board, and prints it.
   Game(char sign1, char sign2)
       : player1(sign1), player2(sign2)
   {
      initBoard();
      printBoard();
   };

   // Starts the game loop.
   void play();
   /* ************************************************** */
};

#endif
