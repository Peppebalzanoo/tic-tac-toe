# Tic-Tac-Toe in C++

This repository contains a simple implementation of the classic Tic-Tac-Toe game in C++ for educational purposes. 

The game runs entirely in the terminal and does not use any graphical libraries.

This project is designed for beginner-level students who want to practice and reinforce their understanding of Object-Oriented Programming (OOP) and C++ fundamentals.

## Installation and Compilation

1. Clone the repository:

   ```sh
   git clone https://github.com/Peppebalzanoo/tic-tac-toe.git
   ```

2. Use the provided `build.sh` script to compile and run the game. The script contains the following commands:

   ```sh
   g++ main.cpp Game.cpp -o tictactoe && ./tictactoe
   ```

3. Run the game manually (if needed):

   ```sh
   ./tictactoe
   ```

## Game Rules

- The game is played on a square grid of any size (e.g., 3x3, 4x4, etc.).
- Two players take turns placing their symbol (X or O) on the grid.
- A player wins by aligning three (or more, depending on the grid size) of their marks in a row, column, or diagonal.
- The game ends in a draw if all cells are filled without a winner.

## Controls

- Players enter the row and column number to place their mark.
- The game ensures that moves are valid, preventing selections outside the grid or on occupied cells.
- The game concludes when a player wins or the grid is completely filled.

## Contributions

Bug reports, suggestions, and improvements are welcome. Feel free to open an issue or submit a pull request!
